FROM ubuntu:22.04

# Install dependencies
RUN apt update && apt install -y \
    build-essential \
    cmake \
    clang \
    gdb \
    git \
    lldb \
    python3 \
    python3-pip \
    libgtest-dev \
    && apt clean

# Create workspace
WORKDIR /app

# Default command
CMD [ "bash" ]
