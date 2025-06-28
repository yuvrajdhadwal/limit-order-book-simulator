FROM ubuntu:22.04

# Install dependencies
RUN apt update && apt install -y \
    build-essential \
    cmake \
    clang \
    gdb \
    git \
    lldb \
    libgtest-dev \
    && apt clean

# Create workspace
WORKDIR /workspace

# Default command
CMD [ "bash" ]
