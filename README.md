
# Cloning

<pre>git clone --recursive https://github.com/letheanVPN/blockchain.git</pre>

# Building

## Dependencies

While older versions might work, we recommend using the specified versions for the best experience.

| Component                                                                                           | Minimum        | Recommended    | Latest Tested  |
|-----------------------------------------------------------------------------------------------------|----------------|----------------|----------------|
| [gcc](https://gcc.gnu.org/) (Linux)                                                                 | 8.4.0          | 9.4.0          | 12.3.0         |
| [llvm/clang](https://clang.llvm.org/) (Linux)                                                       | 7.0.1          | 7.0.1          | 8.0.0          |
| [MSVC](https://visualstudio.microsoft.com/downloads/) (Windows)                                     | 2022 (17.11.5) | 2022 (17.11.5) | 2022 (17.12.3) |
| [XCode](https://developer.apple.com/downloads/) (macOS)                                             | 14.3           | 14.3           | 15.2           |
| [CMake](https://cmake.org/download/)                                                                | 3.26.3         | 3.26.3         | 3.31.6         |
| [Boost](https://www.boost.org/users/download/)                                                      | 1.85.0         | 1.85.0         | 1.85.0         |
| [OpenSSL](https://www.openssl.org/source/) [(win)](https://slproweb.com/products/Win32OpenSSL.html) | 1.1.1n         | 1.1.1w         | 3.4            |
| [Qt](https://download.qt.io/archive/qt/) (GUI only)                                                 | 6.8.3          | 6.8.3          | 6.8.3          |

**Note:** The build instructions below are marked with [*server*] for command-line tools and [*GUI*] for the graphical
interface.

### Linux

Recommended OS versions: Ubuntu 20.04, 22.04 LTS.

#### Prerequisites

##### [*Server Version*]
<pre>sudo apt-get install -y build-essential g++ curl autotools-dev libicu-dev libbz2-dev cmake git screen checkinstall zlib1g-dev libssl-dev bzip2</pre>
##### [*GUI version*]
<pre>sudo apt-get install -y build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev cmake git screen checkinstall zlib1g-dev libssl-dev bzip2 mesa-common-dev libglu1-mesa-dev</pre>
   Make sure you have correct versions installed (see 'Dependencies' section above):
<pre>cmake --version && gcc --version</pre>


3. Clone Zano into a local folder\
   (If for some reason you need to use alternative Zano branch, change 'master' to the required branch name.)

<pre>git clone --recursive https://github.com/hyle-team/zano.git -b master</pre>

   In the following steps we assume that you cloned Zano into '~/zano' folder in your home directory.

    4. Install Qt\
       (*GUI version only, skip this step if you're building server version*)

           [*GUI version*]

<pre>
curl -L -O https://download.qt.io/official_releases/online_installers/qt-online-installer-linux-x64-online.run && 
chmod u+x qt-online-installer-linux-x64-online.run \
./qt-online-installer-linux-x64-online.run \
--accept-licenses \
--default-answer \
--confirm-command install \
qt.qt6.683.linux_gcc_64 \
qt.qt6.683.addons.qt5compat.linux_gcc_64 \
qt.qt6.683.addons.qtpositioning.linux_gcc_64 \
qt.qt6.683.addons.qtwebchannel.linux_gcc_64 \
qt.qt6.683.addons.qtwebsockets.linux_gcc_64 \
qt.qt6.683.addons.qtwebengine.linux_gcc_64 \
qt.qt6.683.addons.qtwebview.linux_gcc_64
</pre>
           
This will download the online installer and perform an unattended installation with the Chromium-based WebEngine


5. Install OpenSSL

   We recommend installing OpenSSL v1.1.1w locally unless you would like to use the same version system-wide.\
   (Assuming that <code>$HOME</code> environment variable is set to your home directory. Otherwise, edit line 4
   accordingly.)

       curl -OL https://www.openssl.org/source/openssl-1.1.1w.tar.gz
       echo "cf3098950cb4d853ad95c0841f1f9c6d3dc102dccfcacd521d93925208b76ac8  openssl-1.1.1w.tar.gz" | shasum -c && tar xaf openssl-1.1.1w.tar.gz 
       cd openssl-1.1.1w/
       ./config --prefix=$HOME/openssl --openssldir=$HOME/openssl shared zlib
       make && make test && make install && cd ..


6. [*OPTIONAL*] Set global environment variables for convenient use\
   For instance, by adding the following lines to <code>~/.bashrc</code>

   [*server version*]

       export OPENSSL_ROOT_DIR=/home/user/openssl

    [*GUI version*]

       export OPENSSL_ROOT_DIR=/home/user/openssl  
       export QT_PREFIX_PATH=/home/user/Qt/6.8.3/gcc_64

      **NOTICE: Please edit the lines above according to your actual paths.**
   
      **NOTICE 2:** Make sure you've restarted your terminal session (by reopening the terminal window or reconnecting the server) to apply these changes.

7. Build the binaries
   The build system will automatically download and compile the required version of the Boost library. You do not need
   to install it manually. If you wish to use a pre-existing Boost installation, you can specify its location by setting
   the <code>BOOST_ROOT</code> environment variable before running <code>cmake</code>.

    1. If you skipped step 5 and did not set the environment variables:

           cd zano && mkdir build && cd build
           OPENSSL_ROOT_DIR=$HOME/openssl cmake ..
           make -j1 daemon simplewallet

    2. If you set the variables in step 5:

           cd zano && mkdir build && cd build
           cmake ..
           make -j1 daemon simplewallet

       **NOTICE**: If you are building on a machine with a relatively high amount of RAM or with the proper setting of
       virtual memory, then you can use <code>-j2</code> or <code>-j</code> option to speed up the building process. Use
       with caution.

       **NOTICE 2**: If you'd like to build binaries for the testnet, use <code>cmake -D TESTNET=TRUE ..</code> instead
       of <code>cmake ..</code> .

    1. Build GUI:

       <pre>
       cd zano
       utils/build_script_linux.sh
       </pre>
   Look for the binaries in <code>build</code> folder

<br />

### Windows

Recommended OS version: Windows 7 x64, Windows 11 x64.

1. Install required prerequisites (Boost, Qt, CMake, OpenSSL).
2. Edit paths in <code>utils/configure_local_paths.cmd</code>.
3. Run one of <code>utils/configure_win64_msvsNNNN_gui.cmd</code> according to your MSVC version.
4. Go to the build folder and open generated Zano.sln in MSVC.
5. Build.

In order to correctly deploy Qt GUI application, you also need to do the following:

6. Run <code>PATH_TO_QT\bin\windeployqt.exe PATH_TO_PROJECT_ROOT\build\src\Debug\Zano.exe</code> (choose the Debug or
   Release folder depending on the configuration you built).
7. You can now run the application using one of the following options:
    * Start the program from Visual Studio
    * Run <code>Zano.exe --html-path=PATH_TO_HTML</code>, where PATH_TO_HTML is by default located at
      PATH_TO_PROJECT_ROOT\src\gui\qt-daemon\layout\html
    * Copy the contents of PATH_TO_PROJECT_ROOT\src\gui\qt-daemon\layout\html to a folder named "html" located in the
      same directory as the Zano.exe binary.
      <br />

### macOS

Recommended OS version: macOS Big Sur 11.4 x64.

1. Install required prerequisites.
2. Set environment variables as stated in <code>utils/macosx_build_config.command</code>.
3. <code>mkdir build</code> <br> <code>cd build</code> <br> <code>cmake ..</code> <br> <code>make</code>

To build GUI application:

1. Create self-signing certificate via Keychain Access:\
   a. Run Keychain Access.\
   b. Choose Keychain Access > Certificate Assistant > Create a Certificate.\
   c. Use “Zano” (without quotes) as certificate name.\
   d. Choose “Code Signing” in “Certificate Type” field.\
   e. Press “Create”, then “Done”.\
   f. Make sure the certificate was added to keychain "System". If not—move it to "System".\
   g. Double click the certificate you've just added, enter the trust section and under "When using this certificate"
   select "Always trust".\
   h. Unfold the certificate in Keychain Access window and double click the underlying private key "Zano". Select "
   Access Control" tab, then select "Allow all applications to access this item". Click "Save Changes".
2. Revise building script, comment out unwanted steps and run it:  <code>utils/build_script_mac_osx.sh</code>
3. The application should be here: <code>/buid_mac_osx_64/release/src</code>

