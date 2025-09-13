# 1. Base Image
FROM python:3.12-slim-bookworm

LABEL authors="snider"

# 2. Install build tools and dependencies for the blockchain project
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    g++ \
    curl \
    cmake \
    git \
    libicu-dev \
    libbz2-dev \
    zlib1g-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# 3. Install uv - the python package manager
RUN curl -LsSf https://astral.sh/uv/install.sh | sh
ENV PATH="/root/.local/bin:$PATH"

# 4. Copy dependency definitions and install them
WORKDIR /app
COPY ./context/pyproject.toml ./context/uv.lock* ./
# Use 'uv pip install .' to install the project and its dependencies from pyproject.toml
RUN uv pip install --system .

# 5. Copy the MCP server source code
COPY ./context .

# 6. Set the entrypoint to run the server
# The working directory for the cmake project will be passed as an argument.
ENTRYPOINT ["python", "-m", "mcp_cmake.server"]

EXPOSE 36908

# Default to /workspace, which can be mounted as a volume
CMD ["-w", "/workspace", "--http", "--host", "0.0.0.0", "--port", "36908"]
