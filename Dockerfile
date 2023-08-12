FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y dist-upgrade && \
    apt-get -y autoremove && \
    apt-get install -y build-essential gdb wget git libssl-dev clang-format && \
    mkdir ~/temp && cd ~/temp && \
    apt-get install -y cmake && \
    cd ~/temp &&  wget -q https://sourceforge.net/projects/boost/files/boost/1.81.0/boost_1_81_0.tar.gz && \
    tar -zxf boost_1_81_0.tar.gz && cd ~/temp/boost_1_81_0 && ./bootstrap.sh && ./b2 cxxflags="-std=c++11" --reconfigure --with-fiber --with-context --with-atomic --with-date_time --with-filesystem --with-url install && \
    cd ~/temp && git clone -b v1.15 https://github.com/linux-test-project/lcov.git && cd lcov && make install && cd .. && \
    apt-get install -y libperlio-gzip-perl libjson-perl && \
    rm -rf ~/temp/* && \
    apt-get autoremove -y &&\
    apt-get clean -y &&\
    rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/okyfirmansyah/libasyik && \
    cd libasyik && \
    git submodule update --init --recursive && \
    mkdir build && \
    cd build && \
    cmake -DLIBASYIK_ENABLE_SOCI=OFF .. && \
    make -j4 && \
    make install

RUN apt-get update && apt-get install -y libopencv-dev

COPY ./src /app/src
COPY ./include /app/include
COPY ./external /app/external
COPY ./tests /app/tests
COPY ./CMakeLists.txt /app

WORKDIR /app/build

RUN mkdir build && \
    cd build && \
    cmake .. && \
    make -j4 && \