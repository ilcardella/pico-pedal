FROM ubuntu:latest AS builder

ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update \
    && apt-get install -y \
    curl \
    build-essential \
    cmake \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Install the RPi Zero toolchain
ARG TOOLCHAIN_URL=https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Buster/GCC%209.3.0/Raspberry%20Pi%201%2C%20Zero/cross-gcc-9.3.0-pi_0-1.tar.gz/download
RUN curl -L ${TOOLCHAIN_URL} | tar -xz -C /opt

# Install BCM2835 library
ARG GCC_TOOLCHAIN=/opt/cross-pi-gcc-9.3.0-0/bin/arm-linux-gnueabihf-gcc
ARG BCM2835_VERSION=1.69
ARG BCM2835_URL=http://www.airspayce.com/mikem/bcm2835/bcm2835-${BCM2835_VERSION}.tar.gz
ARG BCM2835_INSTALL_PATH=/usr/local
RUN curl -L ${BCM2835_URL} | tar -xz -C /opt \
    && cd /opt/bcm2835-${BCM2835_VERSION} \
    && ./configure -host=arm -prefix=${BCM2835_INSTALL_PATH} CC=${GCC_TOOLCHAIN} \
&& make \
&& make install
