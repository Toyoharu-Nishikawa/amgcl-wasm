# create amgcl wasm model

## step1: create docker image
```
git glone https://github.com/ddemidov/amgcl.git
cd amgcl
docker build -f . ./docker/Dockerfile -t amgcl-cpu
```

## step2: build wasm
```
# install emscripten and boost
cd data
./01-emscripten.sh
./02-boost.sh
cd ../

# run docker container and enter into docker container
docker-compose up -d
docker exec -it amgcl_cpu_1 /bin/bash

# turn emcc enable
apt install python3
source ./emsdk/emsdk_env.sh

# make amgcl.js and amgcl.wasm
make
```
