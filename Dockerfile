FROM ubuntu:18.04 as build

RUN apt-get update && apt-get upgrade -y

RUN apt-get install -y build-essential g++ libboost-all-dev python-dev autotools-dev wget libicu-dev libbz2-dev cmake git screen mesa-common-dev libglu1-mesa-dev

WORKDIR /Lethean

COPY . .

RUN make -j15