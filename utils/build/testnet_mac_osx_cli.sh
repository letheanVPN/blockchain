set -x # echo on
set +e # switch off exit on error
curr_path=$(pwd)

# check that all the required environment vars are set
: "${ZANO_BOOST_ROOT:?variable not set, see also macosx_build_config.command}"
: "${ZANO_BOOST_LIBS_PATH:?variable not set, see also macosx_build_config.command}"
: "${CMAKE_OSX_SYSROOT:?CMAKE_OSX_SYSROOT should be set to macOS SDK path, e.g.: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.13.sdk}"
: "${OPENSSL_ROOT_DIR:?variable not set, see also macosx_build_config.command}"

ARCHIVE_NAME_PREFIX=lethean-macos-cli-x64-

if [ -n "$build_prefix" ]; then
  ARCHIVE_NAME_PREFIX=${ARCHIVE_NAME_PREFIX}${build_prefix}-
  build_prefix_label="$build_prefix "
fi


testnet_def="-D TESTNET=TRUE"
testnet_label="testnet "
ARCHIVE_NAME_PREFIX=${ARCHIVE_NAME_PREFIX}testnet-


rm -rf build; mkdir -p build/release; cd build/release;

cmake $testnet_def -D OPENSSL_ROOT_DIR=$OPENSSL_ROOT_DIR -D CMAKE_OSX_SYSROOT=$CMAKE_OSX_SYSROOT -D CMAKE_BUILD_TYPE=Release -D BOOST_ROOT="$ZANO_BOOST_ROOT" -D BOOST_LIBRARYDIR="$ZANO_BOOST_LIBS_PATH" ../..
if [ $? -ne 0 ]; then
    echo "Failed to cmake"
    exit 1
fi

make -j2 connectivity_tool daemon simplewallet
if [ $? -ne 0 ]; then
    echo "Failed to make binaries!"
    exit 1
fi


rm -rf Lethean;
mkdir -p Lethean;

chmod 0777 ./src/letheand src/simplewallet src/connectivity_tool
cp -Rv src/letheand src/simplewallet  src/connectivity_tool ./Lethean

read version_str <<< $(./src/letheand --version | awk '/^Lethean/ { print $2 }')
version_str=${version_str}
echo $version_str

package_filename=${ARCHIVE_NAME_PREFIX}${version_str}.tar.bz2

rm -f ./$package_filename
tar -cjvf $package_filename Lethean
if [ $? -ne 0 ]; then
    echo "Failed to pack"
    exit 1
fi


echo "Build success"
exit 0
