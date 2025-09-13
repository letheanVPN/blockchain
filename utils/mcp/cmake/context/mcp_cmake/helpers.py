# mcp_cmake/helpers.py

import json
from typing import Any, Dict, List

from .models import ErrorDetail


def format_error_for_llm_analysis(error_output: str, error_format: str) -> Dict[str, Any]:
    """
    Parses structured error output (JSON/SARIF) from compilers and converts
    it into the unified API response format.
    """
    errors: List[ErrorDetail] = []
    warnings: List[ErrorDetail] = []

    if error_format == "json":
        try:
            # GCC/Clang JSON output is a list of diagnostic objects
            diagnostics = json.loads(error_output)
            for diag in diagnostics:
                # Simplified parsing, assuming a certain structure
                # This might need to be more robust based on real compiler output
                for location in diag.get("locations", []):
                    detail = ErrorDetail(
                        file_path=location.get("caret", {}).get("file"),
                        line=location.get("caret", {}).get("line"),
                        column=location.get("caret", {}).get("column"),
                        message=diag.get("message", "Unknown error"),
                        severity=diag.get("kind", "error"),
                    )
                    if detail.severity == "error":
                        errors.append(detail)
                    else:
                        warnings.append(detail)
        except json.JSONDecodeError:
            # Fallback for malformed JSON
            errors.append(ErrorDetail(message=error_output, severity="error"))

    elif error_format == "sarif":
        try:
            # SARIF is a complex format, this is a highly simplified parser
            sarif_log = json.loads(error_output)
            for run in sarif_log.get("runs", []):
                for result in run.get("results", []):
                    level = result.get("level", "error")
                    message = result.get("message", {}).get("text", "Unknown error")
                    for location in result.get("locations", []):
                        phys_loc = location.get("physicalLocation", {})
                        artifact_loc = phys_loc.get("artifactLocation", {})
                        region = phys_loc.get("region", {})
                        detail = ErrorDetail(
                            file_path=artifact_loc.get("uri"),
                            line=region.get("startLine"),
                            column=region.get("startColumn"),
                            message=message,
                            severity=level,
                        )
                        if level == "error":
                            errors.append(detail)
                        else:
                            warnings.append(detail)
        except json.JSONDecodeError:
            errors.append(ErrorDetail(message=error_output, severity="error"))

    else:  # raw format
        errors.append(ErrorDetail(message=error_output, severity="error"))

    summary = f"Operation failed with {len(errors)} error(s) and {len(warnings)} warning(s)."

    return {
        "summary": summary,
        "errors": [e.dict() for e in errors],
        "warnings": [w.dict() for w in warnings],
    }
