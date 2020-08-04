#!/bin/sh
set =x
SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-tmp_build}
mkdir -p $BUILD_DIR \
    && cd $BUILD_DIR \
    && cmake $SOURCE_DIR\
    && make
