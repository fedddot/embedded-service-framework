FROM alpine:latest AS base_image

RUN apk update
RUN apk add git make gcc g++ gdb cmake clang-extra-tools

ENV HOME /root
COPY docker/shell_additions ${HOME}
RUN echo "source ${HOME}/shell_additions" >> ${HOME}/.bashrc

WORKDIR /usr/app/src

ENTRYPOINT ["sh"]