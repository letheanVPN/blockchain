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

ARCHIVE_NAME_PREFIX=testnet-lethean-linux-amd64-cli

if [ -n "$build_prefix" ]; then
  ARCHIVE_NAME_PREFIX=${ARCHIVE_NAME_PREFIX}${build_prefix}-
  build_prefix_label="$build_prefix "
fi

if [ $(conan --version &> /dev/null; echo $?) -eq 0 ]; then
  echo "Conan is installed."
elif [ $(pip list | grep -Fq "conan"; echo $?) -eq 0 ]; then
  echo "Conan is installed (verified via pip)."
else
  echo "Conan does not appear to be installed. Installing..."
  pip install conan  # Install Conan
fi

# install conan user settings override
conan config install contrib/cmake/settings_user.yml

curr_path=$(pwd)

# Get the number of available CPU threads
num_threads=$(nproc)

# Calculate desired number of jobs, ensuring a minimum of 1
desired_jobs=$((num_threads - 1))
desired_jobs=$((desired_jobs > 0 ? desired_jobs : 1))


testnet_def="-D TESTNET=TRUE"
testnet_label="testnet "
ARCHIVE_NAME_PREFIX=${ARCHIVE_NAME_PREFIX}testnet

prj_root=$(pwd)

echo "---------------- BUILDING PROJECT ----------------"
echo "--------------------------------------------------"

echo "Building...."

rm -rf build; mkdir -p build/release; cd build/release;

cmake $testnet_def -D STATIC=true -D ARCH=x86-64 -D CMAKE_BUILD_TYPE=Release -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES="${curr_path}"/contrib/cmake/conan_provider.cmake ../..
if [ $? -ne 0 ]; then
    echo "Failed to run cmake"
    exit 1
fi

make -j"$desired_jobs" daemon lethean-wallet connectivity_tool
if [ $? -ne 0 ]; then
    echo "Failed to make!"
    exit 1
fi


rm -rf lethean;
mkdir -p lethean;

chmod 0777 ./src/letheand src/lethean-cli-wallet  src/connectivity_tool
cp -Rv src/letheand src/lethean-cli-wallet  src/connectivity_tool ./lethean


package_filename=${ARCHIVE_NAME_PREFIX}.tar.bz2

rm -f ./$package_filename
cd lethean
tar -cjvf ../../$package_filename *
if [ $? -ne 0 ]; then
    echo "Failed to pack"
    exit 1
fi

echo "Build success"



exit 0
