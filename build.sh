set -e

echo "[ForgeIt Build]: Initialize build."

mkdir -p build 
cmake -S . -B build

echo "[ForgeIt Build]: Using $(nproc) cores for build." 
cmake --build build --parallel ${nproc}

echo "[ForgeIt Build]: the build was successful. The binary file is located in ./build/."

