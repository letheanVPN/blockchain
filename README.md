# Addresses 

- `iT`/`0x73f7` - Main prefix 
- `iTH`/`0x6af7` - integrated paymennt_id address prefix
- `iTHn`/`0xdeaf7` - auditable wallet address
- `iTHa`/`0x7eaf7` -  auditable integrated paymennt_id address prefix

## Cloning

Be sure to clone the repository properly:\
`$ git clone --recursive https://github.com/letheanVPN/blockchain-iTw3.git`

# Building
--------


### Dependencies
| component / version | minimum <br>(not recommended but may work) | recommended | most recent of what we have ever tested |
|--|--|--|--|
| gcc (Linux) | 5.4.0 | 7.4.0 | 8.3.0 |
| llvm/clang (Linux) | UNKNOWN | 7.0.1 | 8.0.0 |
| [MSVC](https://visualstudio.microsoft.com/downloads/) (Windows) | 2015 (14.0 update 1) | 2017 (15.9.0) | 2019 |
| [XCode](https://developer.apple.com/downloads/) (macOS) | 9.2 | 12.3 | 12.3 |
| [CMake](https://cmake.org/download/) | 2.8.6 | 3.15.5 | 3.20 |
| [Boost](https://www.boost.org/users/download/) | 1.70 | 1.70 | 1.76 |
| [OpenSSL](https://www.openssl.org/source/) [(win)](https://slproweb.com/products/Win32OpenSSL.html) | - | 1.1.1n | 1.1.1n | 
| [Qt](https://download.qt.io/archive/qt/) (*only for GUI*) | 5.8.0 | 5.11.2 | 5.15.2 |

Note:\
[*server version*] denotes steps required for building command-line tools (daemon, simplewallet, etc.).\
[*GUI version*] denotes steps required for building LTHN executable with GUI.

<br />

### Linux

Recommended OS version: Ubuntu 18.04 LTS.

1. Prerequisites

   [*server version*]
   
       sudo apt-get install -y build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev cmake git screen checkinstall zlib1g-dev
          
   [*GUI version*]

       sudo apt-get install -y build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev cmake git screen checkinstall zlib1g-dev mesa-common-dev libglu1-mesa-dev

2. Download and build Boost

       curl -OL https://boostorg.jfrog.io/artifactory/main/release/1.70.0/source/boost_1_70_0.tar.bz2
       tar -xjf boost_1_70_0.tar.bz2
       cd boost_1_70_0
       ./bootstrap.sh --with-libraries=system,filesystem,thread,date_time,chrono,regex,serialization,atomic,program_options,locale,timer,log
       ./b2

3. Install Qt\
(*GUI version only, skip this step if you're building server version*)

    [*GUI version*]

       curl -OL https://download.qt.io/new_archive/qt/5.11/5.11.2/qt-opensource-linux-x64-5.11.2.run
       chmod +x qt-opensource-linux-x64-5.11.2.run
       ./qt-opensource-linux-x64-5.11.2.run
    Then follow the instructions in Wizard. Don't forget to tick the WebEngine module checkbox!


4. Install OpenSSL

   We recommend installing OpenSSL v1.1.1n locally unless you would like to use the same version system-wide.

       curl -OL https://www.openssl.org/source/openssl-1.1.1n.tar.gz
       tar xaf openssl-1.1.1n.tar.gz 
       cd openssl-1.1.1n/
       ./config --prefix=/home/user/openssl --openssldir=/home/user/openssl shared zlib
       make
       make test
       make install


5. Set environment variables properly\
For instance, by adding the following lines to `~/.bashrc`

    [*server version*]

       export BOOST_ROOT=/home/user/boost_1_70_0  
       export OPENSSL_ROOT_DIR=/home/user/openssl


    [*GUI version*]

       export BOOST_ROOT=/home/user/boost_1_70_0
       export OPENSSL_ROOT_DIR=/home/user/openssl  
       export QT_PREFIX_PATH=/home/user/Qt5.11.2/5.11.2/gcc_64



6. Build the binaries
   1. Build daemon and simplewallet:

          cd lthn/ && make -j1
      or 
   
          cd lthn && mkdir build && cd build
          cmake ..
          make -j1 daemon simplewallet

      **NOTICE**: If you are building on a machine with a relatively high amount of RAM or with the proper setting of virtual memory, then you can use `-j2` or `-j` option to speed up the building process. Use with caution.
      
      **NOTICE 2**: If you'd like to build binaries for the testnet, use `cmake -D TESTNET=TRUE ..` instead of `cmake ..` .
   
   1. Build GUI:

          cd lthn
          utils/build_script_linux.sh

7. Look for the binaries in `build` folder

<br />

### Windows
Recommended OS versions: Windows 7+ x64.

1. Install [Chocolatey](https://chocolatey.org/install)
2. Install required prerequisites (Boost, Qt, CMake, OpenSSL).

   _NOTE: At time of writing the following versions were available on Chocolatey_
   ```
   choco install boost-msvc-14.2 --version 1.74.0 -y
   choco install qt5-default --version 5.15.2.20211228 -y
   choco install cmake --version 3.23.1 -y 
   choco install openssl --version 1.1.1.1500 -y
   ```

3. Clone repository, then complete the following:
   1. Edit paths in file `utils/configure_local_paths.cmd.example`.
   2. Rename `configure_local_paths.cmd.example` to `configure_local_paths.cmd` (do not commit).
4. Run one of `utils/configure_win64_msvsNNNN_gui.cmd` according to your MSVC version.
5. Go to the build folder and open generated Zano.sln in MSVC.
6. Build.

In order to correctly deploy Qt GUI application, you also need to do the following:

6. Copy Lethean.exe to a folder (e.g. `depoy`). 
7. Run  `PATH_TO_QT\bin\windeployqt.exe deploy\Lethean.exe`.
8. Copy folder `\src\gui\qt-daemon\html` to `deploy\html`.
9. Now you can run `Lethean.exe`

<br />

### macOS
Recommended OS version: macOS Big Sur 11.4 x64.
1. Install required prerequisites.
2. Set environment variables as stated in `utils/macosx_build_config.command`.
3.  `mkdir build` <br> `cd build` <br> `cmake ..` <br> `make`

To build GUI application:

1. Create self-signing certificate via Keychain Access:\
    a. Run Keychain Access.\
    b. Choose Keychain Access > Certificate Assistant > Create a Certificate.\
    c. Use “LetheanVPN” (without quotes) as certificate name.\
    d. Choose “Code Signing” in “Certificate Type” field.\
    e. Press “Create”, then “Done”.\
    f. Make sure the certificate was added to keychain "System". If not—move it to "System".\
    g. Double click the certificate you've just added, enter the trust section and under "When using this certificate" select "Always trust".\
    h. Unfold the certificate in Keychain Access window and double click the underlying private key "LetheanVPN". Select "Access Control" tab, then select "Allow all applications to access this item". Click "Save Changes".
2. Revise building script, comment out unwanted steps and run it:  `utils/build_script_mac_osx.sh`
3. The application should be here: `/buid_mac_osx_64/release/src`

