FROM alpine:latest AS base_image

RUN apk update
RUN apk add git make gcc g++ gdb cmake clang-extra-tools

WORKDIR /usr/app/src

# CMD ["/bin/bash", "-c"]