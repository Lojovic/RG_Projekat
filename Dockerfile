FROM ubuntu:20.04

ENV TZ=Europe/Belgrade
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && \
	apt install -y g++ cmake git build-essential libgl1-mesa-dev libsoil-dev libglm-dev libassimp-dev libglew-dev \
	libglfw3-dev libxinerama-dev libxcursor-dev libxi-dev mesa-common-dev mesa-utils libxxf86vm-dev libfreetype6-dev
	
RUN git clone git@github.com:bob9952/RG_Projekat.git

WORKDIR /usr/src/docker-image	

RUN mkdir build && cd build && cmake .. && make
	
ENTRYPOINT [ "./Sokoban3D" ]	
