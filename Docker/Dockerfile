FROM ubuntu:20.04
LABEL maintainer="kheo1772@gmail.com"

RUN apt-get update && DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC apt-get -y install tzdata
RUN apt-get install -y --no-install-recommends apt-transport-https apt-utils build-essential ca-certificates cmake git wget 
RUN update-ca-certificates

# Install dependencies
RUN apt-get install -y --no-install-recommends libglm-dev libeigen3-dev libopengl-dev libpcl-dev libglfw3-dev

RUN git clone https://github.com/harderthan/interactive-point-cloud.git  --recurse-submodules
RUN mkdir build
WORKDIR /interactive-point-cloud/build
RUN cmake /interactive-point-cloud && make