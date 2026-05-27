set -e

echo "[ForgeIt Build]: Initialize build."

mkdir -p build 
cmake -S . -B build

cmake --build build --parallel ${nproc}

echo "[ForgeIt Build]: the build was successful. The binary file is located in ./build/."