# use --target=builder to return a docker image able to compile the software, probbly used with -v .:/code
FROM ubuntu:24.04 AS builder
LABEL authors="snider"

ARG BUILD_THREADS=1
ARG BUILD_BRANCH=dev
ARG BUILD_LOCAL=1
ARG BUILD_STATIC=0
ARG BUILD_REPO=https://github.com/letheanVPN/blockchain.git
ARG BUILD_TARGET=gcc-linux-x86_64
ARG BUILD_FOLDER=build/release
ARG BUILD_TYPE=Release
ARG BUILD_TESTNET=1
ARG USE_CUSTOM_PROFILE=0


ENV CONAN_HOME=/root/sdk
# CONAN: disables the generation of color escape characters.
ENV NO_COLOR=1
ENV BUILD_TARGET=${BUILD_TARGET}
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt -y upgrade

RUN apt install -y build-essential pkgconf \
    curl ca-certificates bison autotools-dev checkinstall \
    g++ llvm clang lld cmake python-is-python3 \
    git python3 python3-pip python3-dev xz-utils gperf

RUN pip3 install conan --break-system-packages

WORKDIR /

# Copy the build context.
COPY . /tmp/local-src
RUN if [ "$BUILD_LOCAL" = "1" ]; then \
      mv /tmp/local-src /code; \
    else \
      rm -rf /tmp/local-src; \
      git clone --recursive --branch ${BUILD_BRANCH} ${BUILD_REPO} code; \
    fi

VOLUME /code/build/sdk

WORKDIR /code

RUN make release CPU_CORES=${BUILD_THREADS} TESTNET=${BUILD_TESTNET} STATIC=${BUILD_STATIC}
#RUN cmake --build ${BUILD_FOLDER} --config=${BUILD_TYPE} --parallel=${THREADS}

# minor cmd-fu; TESTNEt and MAINNET, in docker context, use MAIINNET binaries names.
# do i like removing `-testnet`, no, but i dislike working around multiple names for ever more, so...
RUN if [ "$BUILD_TESTNET" = "1" ]; then \
      cd ${BUILD_FOLDER}/src && \
      for f in lethean-testnet-*; do \
        ln -s "$f" "$(echo "$f" | sed 's/-testnet//')"; \
      done; \
    fi

# use --target=build-cache to return just the cache files
FROM scratch AS build-cache
COPY --from=builder ${CONAN_HOME} /

# use --target=build-artifacts to return the binaries
FROM scratch AS build-artifacts
COPY --from=builder /code/build/release/src/lethean-* /

# use --target=chain-service to return a working chain node
FROM ubuntu:24.04 AS chain-service

COPY --from=build-artifacts --chmod=+x / /bin

RUN lethean-chain-node --help

ENTRYPOINT ["lethean-chain-node"]