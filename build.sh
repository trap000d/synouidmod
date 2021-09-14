#!/bin/bash

. ./env.sh

$SDK_ROOT/usr/local/$PLATFORM/bin/$PLATFORM-gcc \
   -DNO_PROTO \
   -L$SDK_ROOT/usr/local/$PLATFORM/$PLATFORM/sysroot/usr/lib \
   -lsynosdk \
   synouidmod.c -o synouidmod

$SDK_ROOT/usr/local/$PLATFORM/bin/$PLATFORM-gcc \
   -DNO_PROTO \
   -L$SDK_ROOT/usr/local/$PLATFORM/$PLATFORM/sysroot/usr/lib \
   -lsynosdk \
   synogidmod.c -o synogidmod
