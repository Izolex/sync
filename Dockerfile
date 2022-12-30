FROM debian:bullseye-slim

RUN apt-get update && apt-get install -y \
    build-essential libcmocka-dev cmake vim git gdb \
    && rm -rf /var/lib/apt/lists/*

COPY . /usr/src/app
WORKDIR /usr/src/app

ARG BUILD=./cmake-build-debug
ENV BUILD=${BUILD}

RUN cmake -DCMAKE_BUILD_TYPE=DEBUG -G "Unix Makefiles" -S . -B ${BUILD} &&\
    cmake --build ${BUILD} &&\
    make -C ${BUILD} sync_tests

CMD ${BUILD}/tests/sync_tests
