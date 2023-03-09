#!/bin/bash -x

# Environment prerequisites:
# 1) QT_PREFIX_PATH should be set to Qt libs folder
# 2) BOOST_ROOT should be set to the root of Boost
# 3) OPENSSL_ROOT_DIR should be set to the root of OpenSSL
#
# for example, place these lines to the end of your ~/.bashrc :
#
# export BOOST_ROOT=/home/user/boost_1_66_0
# export QT_PREFIX_PATH=/home/user/Qt5.10.1/5.10.1/gcc_64
# export OPENSSL_ROOT_DIR=/home/user/openssl

ARCHIVE_NAME_PREFIX=lethean-linux-cli-x64-

if [ -n "$build_prefix" ]; then
  ARCHIVE_NAME_PREFIX=${ARCHIVE_NAME_PREFIX}${build_prefix}-
  build_prefix_label="$build_prefix "
fi


testnet_def="-D TESTNET=TRUE"
testnet_label="testnet "
ARCHIVE_NAME_PREFIX=${ARCHIVE_NAME_PREFIX}testnet

prj_root=$(pwd)

echo "---------------- BUILDING PROJECT ----------------"
echo "--------------------------------------------------"

echo "Building...."

rm -rf build; mkdir -p build/release; cd build/release;
cmake $testnet_def -D STATIC=true -D ARCH=x86-64 -D CMAKE_BUILD_TYPE=Release ../..
if [ $? -ne 0 ]; then
    echo "Failed to run cmake"
    exit 1
fi

make -j2 daemon simplewallet connectivity_tool
if [ $? -ne 0 ]; then
    echo "Failed to make!"
    exit 1
fi


rm -rf Lethean;
mkdir -p Lethean;


cp -Rv src/letheand src/simplewallet  src/connectivity_tool ./Lethean
chmod 0777 ./src/letheand src/simplewallet  src/connectivity_tool

package_filename=${ARCHIVE_NAME_PREFIX}.tar.bz2

rm -f ./$package_filename
cd Lethean
tar -cjvf ../$package_filename *
if [ $? -ne 0 ]; then
    echo "Failed to pack"
    exit 1
fi

echo "Build success"



exit 0
