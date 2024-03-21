#!/bin/bash -x

ARCHIVE_NAME_PREFIX=lethean-gui-bundle-linux-testnet-$(arch)


prj_root=$(pwd)

echo "---------------- BUILDING PROJECT ----------------"
echo "--------------------------------------------------"

echo "Building...."

rm -rf build; mkdir -p build/release; cd build/release;
cmake -D TESTNET=TRUE -D STATIC=true -D ARCH=x86-64 -D BUILD_GUI=TRUE -D CMAKE_BUILD_TYPE=Release ../..
if [ $? -ne 0 ]; then
    echo "Failed to run cmake"
    exit 1
fi

make -j2 Lethean
if [ $? -ne 0 ]; then
    echo "Failed to make!"
    exit 1
fi

package_filename=${ARCHIVE_NAME_PREFIX}.tar.bz2

rm -f ./$package_filename
tar -cjvf ../../$package_filename src/lethean-gui-server
if [ $? -ne 0 ]; then
    echo "Failed to pack"
    exit 1
fi

echo "Build success"

exit 0
