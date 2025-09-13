from typing import List, Optional

from pydantic import BaseModel, Field

# Base classes for API responses, as defined in the detailed design document.


class SuccessResponse(BaseModel):
    """Indicates that the operation completed successfully."""

    success: bool = Field(default=True, description="Indicates if the operation was successful.")
    message: str = Field(default="Operation completed successfully.", description="A confirmation message.")


class ErrorDetail(BaseModel):
    """Provides detailed information about a single error or warning."""

    file_path: Optional[str] = Field(None, description="The absolute or relative path to the file.")
    line: Optional[int] = Field(None, description="The line number of the error.")
    column: Optional[int] = Field(None, description="The column number of the error.")
    message: str = Field(..., description="The error or warning message.")
    severity: str = Field(..., description="The severity of the issue, e.g., 'error' or 'warning'.")


class FailureResponse(BaseModel):
    """Indicates that the operation failed, providing details about the errors and warnings."""

    success: bool = Field(default=False, description="Indicates if the operation was successful.")
    summary: str = Field(..., description="A summary of the errors and warnings.")
    errors: List[ErrorDetail] = Field(default_factory=list, description="A list of detailed errors.")
    warnings: List[ErrorDetail] = Field(default_factory=list, description="A list of detailed warnings.")
