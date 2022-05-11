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

#
# Build Lethean
#

FROM ubuntu:18.04 as lethean-build

RUN apt update && \
    apt install -y build-essential \
    libicu-dev \
    curl \
    g++ \
    git


WORKDIR /root

# CMake 3.15.5

RUN curl https://github.com/Kitware/CMake/releases/download/v3.15.5/cmake-3.15.5-Linux-x86_64.sh -OL &&\
    echo '62e3e7d134a257e13521e306a9d3d1181ab99af8fcae66699c8f98754fc02dda cmake-3.15.5-Linux-x86_64.sh' | sha256sum -c - &&\
    mkdir /opt/cmake &&\
    sh cmake-3.15.5-Linux-x86_64.sh --prefix=/opt/cmake --skip-license &&\
    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake &&\
    cmake --version &&\
    rm cmake-3.15.5-Linux-x86_64.sh


# Boost 1.70

RUN curl https://boostorg.jfrog.io/artifactory/main/release/1.70.0/source/boost_1_70_0.tar.bz2 -OL &&\
    echo '430ae8354789de4fd19ee52f3b1f739e1fba576f0aded0897c3c2bc00fb38778 boost_1_70_0.tar.bz2' | sha256sum -c - &&\
    tar -xjf boost_1_70_0.tar.bz2 &&\
    rm boost_1_70_0.tar.bz2 &&\
    cd boost_1_70_0 &&\
    ./bootstrap.sh --with-libraries=system,filesystem,thread,date_time,chrono,regex,serialization,atomic,program_options,locale,timer,log &&\
    ./b2 &&\
    cd ..

ENV BOOST_ROOT=/root/boost_1_70_0


# OpenSSL 1.1.1n

RUN curl https://www.openssl.org/source/openssl-1.1.1n.tar.gz -OL &&\
    echo '40dceb51a4f6a5275bde0e6bf20ef4b91bfc32ed57c0552e2e8e15463372b17a openssl-1.1.1n.tar.gz' | sha256sum -c - &&\
    tar xaf openssl-1.1.1n.tar.gz &&\
    rm openssl-1.1.1n.tar.gz &&\
    cd openssl-1.1.1n &&\
    ./config --prefix=/root/openssl --openssldir=/root/openssl shared zlib &&\
    make &&\
    make test &&\
    make install &&\
    cd .. &&\
    rm -rf openssl-1.1.1n

ENV OPENSSL_ROOT_DIR=/root/openssl


# Zano

RUN pwd && mem_avail_gb=$(( $(getconf _AVPHYS_PAGES) * $(getconf PAGE_SIZE) / (1024 * 1024 * 1024) )) &&\
    make_job_slots=$(( $mem_avail_gb < 4 ? 1 : $mem_avail_gb / 4)) &&\
    echo make_job_slots=$make_job_slots &&\
    set -x &&\
    git clone --single-branch --recursive https://github.com/letheanVPN/blockchain-iTw3.git lethean &&\
    cd lethean &&\
    mkdir build && cd build &&\
    cmake -D STATIC=TRUE .. &&\
    make -j $make_job_slots daemon simplewallet


#
# Run Lethean
#

FROM ubuntu:18.04

RUN useradd -ms /bin/bash lethean &&\
    mkdir -p /home/lethean/.Lethean &&\
    chown -R lethean:lethean /home/lethean/.Lethean

USER lethean:lethean

WORKDIR /home/lethean
COPY --chown=lethean:lethean --from=lethean-build /root/lethean/build/src/letheand .
COPY --chown=lethean:lethean --from=lethean-build /root/lethean/build/src/simplewallet .

# blockchain loaction
VOLUME /home/lethean/data/chain

EXPOSE 11121 11211

ENTRYPOINT ["./letheand"]
CMD ["--disable-upnp", "--rpc-bind-ip=0.0.0.0", "--log-level=0"]
