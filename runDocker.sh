#!/usr/bin/bash

sudo xhost +local:root

docker run \
  --rm \
  -it \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -e DISPLAY=$DISPLAY \
  -e QT_X11_NO_MITSHM=1 \
  sokoban3d \
  bash
