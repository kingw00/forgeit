set -e

echo "[ForgeIt Build]: Initialize build."

mkdir -p build 
cmake -S . -B build

echo "[ForgeIt Build]: Using $(nproc) cores for build." 
cmake --build build --parallel ${nproc}

echo "[ForgeIt Build]: The build was successful."
echo "[ForgeIt Build]: The binary file of the daemon: ./build/forgeit_daemon."
echo "[ForgeIt Build]: The binary file of the client: ./build/forgeit_client."
echo "[ForgeIt Build]: Run daemon first. Client didn't work without daemon."

