#!/bin/sh -e

CXXFLAGS="-std=c++11 -O3"

emcc $CXXFLAGS comper.cc -o comper.bc
emcc $CXXFLAGS enigma.cc -o enigma.bc
emcc $CXXFLAGS kosinski.cc -o kosinski.bc
emcc $CXXFLAGS nemesis.cc -o nemesis.bc
emcc $CXXFLAGS saxman.cc -o saxman.bc
emcc $CXXFLAGS exports.cc -o exports.bc

emcc -s EXPORTED_FUNCTIONS="['_comper_decode', '_comper_encode', '_enigma_decode', '_enigma_encode', '_kosinski_decode', '_kosinski_encode', '_moduled_kosinski_decode', '_moduled_kosinski_encode', '_nemesis_decode', '_nemesis_encode', '_saxman_decode', '_saxman_encode']" comper.bc enigma.bc kosinski.bc nemesis.bc saxman.bc exports.bc -o kensc-tmp.js

cat header.js kensc-tmp.js > kensc.js

rm kensc-tmp.js
rm *.bc
