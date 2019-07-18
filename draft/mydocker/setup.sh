#!/bin/bash


if [! -d "/usr/local"];then
mkdir /usr/local
fi

export HOME=/usr/local

cd /usr/local

if [ ! -d "${HOME}/lib" ]; then
  mkdir ${HOME}/lib
fi

if [ ! -d "${HOME}/include" ]; then
  mkdir ${HOME}/include
fi

apt-get update

apt-get install -yq gcc g++ autotools-dev apt-utils lib64readline6-dev 
apt-get install -yq libhdf5-openmpi-dev libhdf5-openmpi-100 libopenblas-base libopenblas-dev libcurl4-openssl-dev

echo $(which mpicc)

apt-get install -yq git cmake autoconf build-essential rapidjson-dev 

apt-get install -yq libhdf5-dev libhdf5-openmpi-dev armadillo-dev eigen3-dev 

# openmpi stuff 
apt-get install -yq libopenmpi-dev libscalapack-openmpi-dev libopenblas-base libopenblas-dev libcurl4-openssl-dev

cd /usr/include
git clone https://github.com/niXman/yas.git


exit 0
