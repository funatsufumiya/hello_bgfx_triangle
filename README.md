# hello_bgfx_triangle

This is hand writing transcription of https://thatonegamedev.com/cpp/hello-bgfx/ for study. (Upgraded BIG2-stack to v0.0.9)

## Build

```sh
./cmake_init_single_thread.sh # Only first time, for mac (metal)
# ./cmake_init_multi_thread.sh # Only first time, for win/linux
./build.sh
```

## Run

```sh
./run.sh
```

## Status

- [x] GLFW only (`./run.sh glfw_only`)
- [x] GLFW + bgfx basic (`./run.sh basic`)
- [x] Triangle (`./run.sh triangle`)
- [x] Triangle Alt for examinig bgfx API (`./run.sh triangle_alt`)