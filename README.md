Get the repository with

git clone --recursive https://github.com/tjakway/digital-ant-farm.git

or
git clone https://github.com/tjakway/digital-ant-farm.git
git submodule update --init --recursive

Build with:

cd bin
cmake ..
make

Building options:

cmake -DCMAKE_BUILD_TYPE=Debug ..

to build with debugging symbols

cmake -DCMAKE_BUILD_TYPE=DebugWithWarnings ..

to build with a variety of extra compiler flags (see CMakeLists.txt for details)

cmake -DCMAKE_BUILD_TYPE=DebugWithWarningsOptimized ..

to build with all the extra compiler flags of DebugWithWarnings and an added -Og flag for gcc/g++ only (has no effect if not building with a GNU compiler).
