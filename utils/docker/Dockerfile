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
# Available Build Args
#   - CMake Version:    CMAKE_VERSION_DOT, CMAKE_HASH
#   - Boost Version:    BOOST_VERSION, BOOST_VERSION_DOT, BOOST_HASH
#   - OpenSSL Version:  OPENSSL_VERSION_DOT, OPENSSL_HASH
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

FROM ubuntu:18.04 as build-prep


RUN apt update && \
    apt install -y build-essential \
    libicu-dev \
    curl \
    g++ \
    git


WORKDIR /root

# Lib Settings
ARG CMAKE_VERSION_DOT=3.15.5
ARG CMAKE_HASH=62e3e7d134a257e13521e306a9d3d1181ab99af8fcae66699c8f98754fc02dda

ARG BOOST_VERSION=1_70_0
ARG BOOST_VERSION_DOT=1.70.0
ARG BOOST_HASH=430ae8354789de4fd19ee52f3b1f739e1fba576f0aded0897c3c2bc00fb38778

ARG OPENSSL_VERSION_DOT=1.1.1n
ARG OPENSSL_HASH=40dceb51a4f6a5275bde0e6bf20ef4b91bfc32ed57c0552e2e8e15463372b17a

# Environment Variables
ENV BOOST_ROOT /root/boost_${BOOST_VERSION}
ENV OPENSSL_ROOT_DIR=/root/openssl

##########################################################
# Split download & compile to use dockers caching layers #
##########################################################

# Download CMake
RUN set -ex \
    && curl https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION_DOT}/cmake-${CMAKE_VERSION_DOT}-Linux-x86_64.sh -OL\
    && echo "${CMAKE_HASH}  cmake-${CMAKE_VERSION_DOT}-Linux-x86_64.sh" | sha256sum -c

# Download Boost
RUN set -ex \
    && curl -L -o  boost_${BOOST_VERSION}.tar.bz2 https://downloads.sourceforge.net/project/boost/boost/${BOOST_VERSION_DOT}/boost_${BOOST_VERSION}.tar.bz2 \
    &&  sha256sum boost_${BOOST_VERSION}.tar.bz2 \
    && echo "${BOOST_HASH}  boost_${BOOST_VERSION}.tar.bz2" | sha256sum -c\
    && tar -xvf boost_${BOOST_VERSION}.tar.bz2


# Download OpenSSL
RUN curl https://www.openssl.org/source/openssl-${OPENSSL_VERSION_DOT}.tar.gz -OL \
    &&  sha256sum openssl-${OPENSSL_VERSION_DOT}.tar.gz \
    && echo "${OPENSSL_HASH} openssl-${OPENSSL_VERSION_DOT}.tar.gz" | sha256sum -c


# Compile CMake
RUN set -ex \
    && mkdir /opt/cmake \
    && sh cmake-3.15.5-Linux-x86_64.sh --prefix=/opt/cmake --skip-license\
    && ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake\
    && cmake --version\
    && rm cmake-3.15.5-Linux-x86_64.sh

# Compile Boost
RUN set -ex \
    && cd boost_${BOOST_VERSION} \
    && ./bootstrap.sh --with-libraries=system,filesystem,thread,date_time,chrono,regex,serialization,atomic,program_options,locale,timer,log \
    && ./b2

# Compile OpenSSL
RUN set -ex \
    && tar xaf openssl-${OPENSSL_VERSION_DOT}.tar.gz \
    && rm openssl-${OPENSSL_VERSION_DOT}.tar.gz \
    && cd openssl-${OPENSSL_VERSION_DOT} \
    && ./config --prefix=/root/openssl --openssldir=/root/openssl shared zlib \
    && make \
    && make test \
    && make install \
    && cd .. \
    && rm -rf openssl-${OPENSSL_VERSION_DOT}

FROM build-prep as build

#FROM lthn/build:server as build

#ARG THREADS=2

#COPY . /project

#WORKDIR /project/build

#RUN cmake -D STATIC=true -D ARCH=x86-64 -D TESTNET=TRUE -D CMAKE_BUILD_TYPE=Release ..

#RUN make -j${THREADS} daemon simplewallet

#FROM scratch as export
#COPY --chmod=0777 --from=build /project/build/src/letheand /
#COPY --chmod=0777 --from=build /project/build/src/simplewallet /

#FROM ubuntu:20.04 as final

#RUN useradd -ms /bin/bash lethean &&\
#    mkdir -p /home/lethean/data &&\
#    chown -R lethean:lethean /home/lethean/data



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

RUN useradd -ms /bin/bash lethean &&\
    mkdir -p /home/lethean/.Zano &&\
    chown -R lethean:lethean /home/lethean/.Zano

USER lethean:lethean

WORKDIR /home/zano
COPY --chown=lethean:lethean --from=build /root/lethean/build/src/zanod .
COPY --chown=lethean:lethean --from=build /root/lethean/build/src/simplewallet .


# blockchain loaction
VOLUME /home/lethean/data

EXPOSE 31121 31211


ENTRYPOINT ["letheand"]
CMD ["--disable-upnp", "--rpc-bind-ip=0.0.0.0", "--log-level=0", "--data-dir=/home/lethean/data"]
