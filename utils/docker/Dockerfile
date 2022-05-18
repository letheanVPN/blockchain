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
#
# Exporting built binaries can be done targeting the scratch layer and setting the output option
#   docker build -t chain/testnet --target export -o artifacts
#
# Developer builds, to make a build container run the first command, once built, use only the second command
#   1) docker build --target build -t local/chain:developer -f utils/docker/Dockerfile .
#   2) docker run -v $(pwd):/project local/chain:developer

FROM lthn/build:server as build

ARG THREADS=2

COPY . /project

WORKDIR /project/build

RUN cmake -D STATIC=true -D ARCH=x86-64 -D TESTNET=TRUE -D CMAKE_BUILD_TYPE=Release ..

RUN make -j${THREADS} daemon simplewallet

FROM scratch as export
COPY --chmod=0777 --from=build /project/build/src/letheand /
COPY --chmod=0777 --from=build /project/build/src/simplewallet /

FROM ubuntu:20.04 as final

RUN useradd -ms /bin/bash lethean &&\
    mkdir -p /home/lethean/data &&\
    chown -R lethean:lethean /home/lethean/data


RUN set -xe \
    && echo '#!/bin/sh' > /usr/sbin/policy-rc.d\
    && echo 'exit 101' >> /usr/sbin/policy-rc.d\
    && chmod +x /usr/sbin/policy-rc.d\
    && dpkg-divert --local --rename --add /sbin/initctl\
    && cp -a /usr/sbin/policy-rc.d /sbin/initctl\
    && sed -i 's/^exit.*/exit 0/' /sbin/initctl\
    && echo 'force-unsafe-io' > /etc/dpkg/dpkg.cfg.d/docker-apt-speedup\
    && echo 'DPkg::Post-Invoke { "rm -f /var/cache/apt/archives/*.deb /var/cache/apt/archives/partial/*.deb /var/cache/apt/*.bin || true"; };' > /etc/apt/apt.conf.d/docker-clean\
    && echo 'APT::Update::Post-Invoke { "rm -f /var/cache/apt/archives/*.deb /var/cache/apt/archives/partial/*.deb /var/cache/apt/*.bin || true"; };' >> /etc/apt/apt.conf.d/docker-clean\
    && echo 'Dir::Cache::pkgcache ""; Dir::Cache::srcpkgcache "";' >> /etc/apt/apt.conf.d/docker-clean\
    && echo 'Acquire::Languages "none";' > /etc/apt/apt.conf.d/docker-no-languages\
    && echo 'Acquire::GzipIndexes "true"; Acquire::CompressionTypes::Order:: "gz";' > /etc/apt/apt.conf.d/docker-gzip-indexes\
    && echo 'Apt::AutoRemove::SuggestsImportant "false";' > /etc/apt/apt.conf.d/docker-autoremove-suggests

RUN mkdir -p /run/systemd && echo 'docker' > /run/systemd/container

USER lethean:lethean

WORKDIR /home/lethean

COPY --chmod=0777 --chown=root:root --from=export / /usr/bin

# blockchain loaction
VOLUME /home/lethean/data

EXPOSE 31121 31211


ENTRYPOINT ["letheand"]
CMD ["--disable-upnp", "--rpc-bind-ip=0.0.0.0", "--log-level=0", "--data-dir=/home/lethean/data"]
