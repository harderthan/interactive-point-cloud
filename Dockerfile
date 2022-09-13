FROM ubuntu:20.04

LABEL maintainer="kheo1772@gmail.com"

# bootstrap
RUN apt-get update && apt-get install -y --no-install-recommends apt-transport-https ca-certificates wget vim build-essential git cmake
RUN update-ca-certificates

RUN git clone https://github.com/harderthan/interactive-point-cloud.git
RUN mkdir build
WORKDIR /interactive-point-cloud/build
RUN cmake /interactive-point-cloud && make
