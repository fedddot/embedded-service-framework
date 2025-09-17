FROM debian:bookworm-slim AS base_image

RUN apt-get update
RUN apt-get install -y make gcc g++ gdb cmake
RUN apt-get install -y git
RUN apt-get install -y wget
RUN apt-get install -y locales

RUN rm -rf /var/lib/apt/lists/* && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG=en_US.utf8
ENV LC_ALL=en_US.utf8

WORKDIR /usr/app/external/llvm
RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh
RUN ./llvm.sh 18
ENV PATH=${PATH}:/usr/lib/llvm-18/bin

# Sources root dir should be mounted to this location when running the container
WORKDIR /usr/app/src

CMD ["/bin/bash", "-c"]