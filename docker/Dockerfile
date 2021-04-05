FROM ubuntu:latest AS builder

ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update \
    && apt-get install -y \
    curl \
    build-essential \
    cmake \
    python3 \
    && rm -rf /var/lib/apt/lists/*
