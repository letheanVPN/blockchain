###########################################################################################
## letheand Dockerfile
###########################################################################################

#
# Usage:
# (make sure you have correct permission for /var/data/lethean-data prior to run!)
#
#   docker run --restart=always -v /var/data/lethean-data:/home/lethean/.Lethean -p 11121:11121 -p 11211:11211 --name=letheand -dit sowle/lethean-full-node
#
# To get into container and interact with the daemon:
#   docker attach letheand
#
# To detach from container and left it running:
#   Ctrl+P, Ctrl+Q
#
# To stop container:
#   docker stop letheand
#
# To build with different lib versions, pass through --build-arg's
#   docker build --build-arg OPENSSL_VERSION_DOT=1.1.1n --build-arg OPENSSL_HASH=40dceb51a4f6a5275bde0e6bf20ef4b91bfc32ed57c0552e2e8e15463372b17a -f utils/docker/Dockerfile .
#
# To adjust the threads used
#   docker build --build-arg THREADS=10 -t chain/testnet .
#
# Available Build Args
#   - Build Jobs:       THREADS=2
#   - CMake Version:    CMAKE_VERSION_DOT, CMAKE_HASH
#   - Boost Version:    BOOST_VERSION, BOOST_VERSION_DOT, BOOST_HASH
#   - OpenSSL Version:  OPENSSL_VERSION_DOT, OPENSSL_HASH

FROM lthn/build:server as build

ARG THREADS=2

COPY . /project

WORKDIR /project/build

RUN cmake -D STATIC=true -D ARCH=x86-64 -D TESTNET=TRUE -D CMAKE_BUILD_TYPE=Release ..

RUN make -j${THREADS} daemon simplewallet

# Export stage; scratch is a empty fs you can use this image to build the assets with
#   docker build -t chain/testnet --target export -o artifacts
#
# Developer builds
#   docker run -v $(pwd):/project --target export -o artifacts lthn/chain:developer

FROM scratch as export
COPY --chmod=0777 --from=build /project/build/src/letheand /
COPY --chmod=0777 --from=build /project/build/src/simplewallet /

FROM ubuntu:20.04 as final

RUN useradd -ms /bin/bash lethean &&\
    mkdir -p /home/lethean/data &&\
    chown -R lethean:lethean /home/lethean/data

USER lethean:lethean

WORKDIR /home/lethean

COPY --chmod=0777 --chown=lethean:lethean --from=export / .

# blockchain loaction
VOLUME /home/lethean/data

EXPOSE 31121 31211

ENTRYPOINT ["./letheand"]
CMD ["--disable-upnp", "--non-interactive", "--rpc-bind-ip=0.0.0.0", "--log-level=0", "--data-dir=/home/lethean/data"]