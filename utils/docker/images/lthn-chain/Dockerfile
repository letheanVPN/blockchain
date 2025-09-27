# This is a multi target docker image
FROM ubuntu:24.04 AS builder
LABEL authors="snider"

ARG THREADS=1
ARG BUILD_BRANCH=dev-configure-testnet-1
ARG BUILD_LOCAL=1
ARG BUILD_REPO=https://github.com/letheanVPN/blockchain.git
ARG BUILD_TARGET=gcc-linux-arm64
ARG BUILD_FOLDER=build/release
ARG BUILD_TYPE=Release
ARG BUILD_TESTNET=0


ENV CONAN_HOME=/root/sdk
ENV BUILD_TARGET=${BUILD_TARGET}

RUN apt update && apt -y upgrade

RUN apt install -y build-essential pkgconf \
    curl ca-certificates \
    g++ llvm clang lld cmake \
    git python3 python3-pip xz-utils gperf

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

WORKDIR /code

RUN conan profile detect --name=default --force

RUN conan install . --output-folder=${BUILD_FOLDER} --build=missing -s build_type=${BUILD_TYPE} -pr:h=/code/cmake/profiles/$BUILD_TARGET

RUN cmake -S /code -B ${BUILD_FOLDER} -DCMAKE_TOOLCHAIN_FILE=${BUILD_FOLDER}/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DTESTNET=${BUILD_TESTNET}

RUN cmake --build ${BUILD_FOLDER} --config=${BUILD_TYPE} --parallel=${THREADS}


FROM scratch AS build-cache
COPY --from=builder ${CONAN_HOME} /

FROM scratch AS build-artifacts
COPY --from=builder /code/build/release/src/lethean-* /

#FROM ubuntu:24.04 AS chain-service
#
#COPY --from=build-artifacts --chmod=+x / /bin
#
#RUN lethean-testnet-chain-node --help
