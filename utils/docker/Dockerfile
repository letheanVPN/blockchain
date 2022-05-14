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

FROM ubuntu:20.04 as lethean-build
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update
RUN apt-get install -y build-essential libicu-dev git curl g++ libssl-dev make pkg-config libboost-all-dev \
    zlib1g-dev mesa-common-dev libglu1-mesa-dev python-dev autotools-dev libbz2-dev cmake screen checkinstall

COPY . /root/lethean

WORKDIR /root/lethean

WORKDIR /root/lethean/build

RUN cmake -D TESTNET=TRUE ..

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
COPY --chmod=0777 --chown=lethean:lethean --from=lethean-build /root/lethean/build/src/letheand .
COPY --chmod=0777 --chown=lethean:lethean --from=lethean-build /root/lethean/build/src/simplewallet .

# blockchain loaction
VOLUME /home/lethean/data/chain

EXPOSE 31121 31211

ENTRYPOINT ["./letheand"]
CMD ["--disable-upnp", "--rpc-bind-ip=0.0.0.0", "--log-level=0", "--data-dir=/home/lethean/data/chain"]
