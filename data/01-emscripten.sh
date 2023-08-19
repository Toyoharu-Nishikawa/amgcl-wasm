
apt install -y python3  xz-utils bzip2
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

git pull

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source emsdk_env.sh
cd ../


make
