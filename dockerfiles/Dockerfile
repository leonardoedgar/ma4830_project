FROM ubuntu:18.04
MAINTAINER Leonardo Edgar

ARG USER
ARG GROUP
ARG UID
ARG GID

# Install core linux tools
RUN apt-get update && apt-get install -y --no-install-recommends \
	apt-utils lsb-release sudo unzip wget ssh vim curl ca-certificates gnupg \
	&& rm -rf /var/lib/apt/lists/* 

# Install programs
RUN apt-get update && apt-get install -y --no-install-recommends build-essential \ 
	wget gcc git bundler libssl-dev \
	&& rm -rf /var/lib/apt/lists/*

# Build CMake from source
RUN wget https://github.com/Kitware/CMake/releases/download/v3.18.1/cmake-3.18.1.tar.gz \
	&& tar -zxvf cmake-3.18.1.tar.gz 
RUN cd cmake-3.18.1 && ./bootstrap && make -j4 && make install

# User and permissions
ARG HOME=/home/${USER}
RUN mkdir -p /etc/sudoers.d \
    && groupadd -g ${GID} ${GROUP} \
    && useradd -d ${HOME} -u ${UID} -g ${GID} -m -s /bin/bash ${USER} \
    && echo "${USER} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/sudoers_${USER}
USER ${USER}


WORKDIR ${HOME}

# Install CMock
COPY --chown=${USER} lib/cmock			lib/cmock
RUN cd lib/cmock && bundle install
