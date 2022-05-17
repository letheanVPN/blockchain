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

FROM ubuntu:20.04 as build-prep
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update
RUN apt-get install -y build-essential libicu-dev git curl g++ libssl-dev make pkg-config libboost-all-dev \
    zlib1g-dev mesa-common-dev libglu1-mesa-dev python-dev autotools-dev libbz2-dev cmake screen checkinstall

WORKDIR /root

##########################################################
# Split download & compile to use dockers caching layers #
##########################################################

# Download CMake
ARG CMAKE_VERSION_DOT=3.15.5
ARG CMAKE_HASH=62e3e7d134a257e13521e306a9d3d1181ab99af8fcae66699c8f98754fc02dda
RUN set -ex \
    && curl https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION_DOT}/cmake-${CMAKE_VERSION_DOT}-Linux-x86_64.sh -OL\
    && echo "${CMAKE_HASH}  cmake-${CMAKE_VERSION_DOT}-Linux-x86_64.sh" | sha256sum -c

# Download Boost
ARG BOOST_VERSION=1_70_0
ARG BOOST_VERSION_DOT=1.70.0
ARG BOOST_HASH=430ae8354789de4fd19ee52f3b1f739e1fba576f0aded0897c3c2bc00fb38778
RUN set -ex \
    && curl -L -o  boost_${BOOST_VERSION}.tar.bz2 https://downloads.sourceforge.net/project/boost/boost/${BOOST_VERSION_DOT}/boost_${BOOST_VERSION}.tar.bz2 \
    &&  sha256sum boost_${BOOST_VERSION}.tar.bz2 \
    && echo "${BOOST_HASH}  boost_${BOOST_VERSION}.tar.bz2" | sha256sum -c\
    && tar -xvf boost_${BOOST_VERSION}.tar.bz2


# Download OpenSSL
ARG OPENSSL_VERSION_DOT=1.1.1n
ARG OPENSSL_HASH=40dceb51a4f6a5275bde0e6bf20ef4b91bfc32ed57c0552e2e8e15463372b17a

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
ENV BOOST_ROOT /root/boost_${BOOST_VERSION}

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

ENV OPENSSL_ROOT_DIR=/root/openssl

FROM build-prep as build

COPY . /root/lethean

WORKDIR /root/lethean/build

RUN cmake -D STATIC=true -D ARCH=x86-64 -D TESTNET=TRUE -D CMAKE_BUILD_TYPE=Release ..

RUN make -j2 daemon simplewallet


#
# Run Lethean
#

FROM ubuntu:20.04

RUN useradd -ms /bin/bash lethean &&\
    mkdir -p /home/lethean/data &&\
    chown -R lethean:lethean /home/lethean/data

USER lethean:lethean

WORKDIR /home/lethean
COPY --chmod=0777 --chown=lethean:lethean --from=build /root/lethean/build/src/letheand .
COPY --chmod=0777 --chown=lethean:lethean --from=build /root/lethean/build/src/simplewallet .
COPY --chmod=0777 --chown=lethean:lethean --from=build /root/lethean/build/src/*.a .

# blockchain loaction
VOLUME /home/lethean/data/chain

EXPOSE 31121 31211

ENTRYPOINT ["./letheand"]
CMD ["--disable-upnp", "--rpc-bind-ip=0.0.0.0", "--log-level=0", "--data-dir=/home/lethean/data/chain"]