set -x # echo on
set +e # switch off exit on error
curr_path=${BASH_SOURCE%/*}

# check that all the required environment vars are set
: "${ZANO_QT_PATH:?variable not set, see also macosx_build_config.command}"
: "${ZANO_BOOST_ROOT:?variable not set, see also macosx_build_config.command}"
: "${ZANO_BOOST_LIBS_PATH:?variable not set, see also macosx_build_config.command}"
: "${CMAKE_OSX_SYSROOT:?CMAKE_OSX_SYSROOT should be set to macOS SDK path, e.g.: /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.13.sdk}"
: "${OPENSSL_ROOT_DIR:?variable not set, see also macosx_build_config.command}"


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


ARCHIVE_NAME_PREFIX=lethean-gui-bundle-macos-testnet-$(arch)

rm -rf build; mkdir -p build/release; cd build/release;

cmake -D TESTNET=TRUE -D OPENSSL_ROOT_DIR=$OPENSSL_ROOT_DIR -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=contrib/cmake/conan_provider.cmake -D CMAKE_OSX_SYSROOT=$CMAKE_OSX_SYSROOT -D BUILD_GUI=TRUE -D CMAKE_PREFIX_PATH="$ZANO_QT_PATH" -D CMAKE_BUILD_TYPE=Release -D BOOST_ROOT="$ZANO_BOOST_ROOT" -D BOOST_LIBRARYDIR="$ZANO_BOOST_LIBS_PATH" ../..
if [ $? -ne 0 ]; then
    echo "Failed to cmake"
    exit 1
fi

make -j2 Lethean
if [ $? -ne 0 ]; then
    echo "Failed to make Lethean"
    exit 1
fi

cd src/
if [ $? -ne 0 ]; then
    echo "Failed to cd src"
    exit 1
fi

# copy all necessary libs into the bundle in order to workaround El Capitan's SIP restrictions
mkdir -p lethean-gui-server.app/Contents/Frameworks/boost_libs
cp -R "$ZANO_BOOST_LIBS_PATH/" lethean-gui-server.app/Contents/Frameworks/boost_libs/
if [ $? -ne 0 ]; then
    echo "Failed to cp workaround to MacOS"
    exit 1
fi

# fix boost libs paths in main executable and libs to workaround El Capitan's SIP restrictions

source $(pwd)/../../../utils/build/extras/macos/fix_boost_libs_path.sh

fix_boost_libs_in_binary @executable_path/../Frameworks/boost_libs lethean-gui-server.app/Contents/MacOS/lethean-gui-server
fix_boost_libs_in_libs @executable_path/../Frameworks/boost_libs lethean-gui-server.app/Contents/Frameworks/boost_libs



"$ZANO_QT_PATH/bin/macdeployqt" lethean-gui-server.app
if [ $? -ne 0 ]; then
    echo "Failed to macdeployqt lethean-gui-server.app"
    exit 1
fi

echo "############### Prepearing archive... ################"
package_filename=${ARCHIVE_NAME_PREFIX}.tar.bz2

rm -f ./$package_filename
cd lethean-gui-server.app
tar -cjvf ../../../../$package_filename *

echo "Build success"
