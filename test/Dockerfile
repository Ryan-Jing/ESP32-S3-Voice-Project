FROM espressif/idf:v5.4

ARG DEBIAN_FRONTEND=noninteractive
ARG CONTAINER_USER=esp
ARG USER_UID=1050
ARG USER_GID=$USER_UID

RUN apt-get update && \
    apt install -y -q \
    cmake \
    git \
    libglib2.0-0 \
    libsdl2-2.0-0 \
    libnuma1 \
    libpixman-1-0 \
    libslirp0 \
    wget \
    && rm -rf /var/lib/apt/lists/*

ENV QEMU_REL=esp_develop_9.0.0_20240606
ENV QEMU_SHA256=071d117c44a6e9a1bc8664ab63b592d3e17ceb779119dcb46c59571a4a7a88c9
ENV QEMU_DIST=qemu-xtensa-softmmu-${QEMU_REL}-x86_64-linux-gnu.tar.xz
ENV QEMU_URL=https://github.com/espressif/qemu/releases/download/esp-develop-9.0.0-20240606/${QEMU_DIST}

RUN wget --no-verbose ${QEMU_URL} && \
    # Update the SHA256 below with the correct value from the QEMU release page!
    echo "${QEMU_SHA256} *${QEMU_DIST}" | sha256sum --check --strict - && \
    tar -xf ${QEMU_DIST} -C /opt && \
    rm ${QEMU_DIST}

ENV PATH=/opt/qemu/bin:${PATH}

RUN groupadd --gid $USER_GID $CONTAINER_USER && \
    adduser --uid $USER_UID --gid $USER_GID --disabled-password --gecos "" ${CONTAINER_USER} && \
    usermod -a -G root $CONTAINER_USER && \
    usermod -a -G dialout $CONTAINER_USER

RUN chmod -R 775 /opt/esp/python_env/

RUN echo "source /opt/esp/idf/export.sh > /dev/null 2>&1" >> ~/.bashrc

# RUN echo $($IDF_PATH/tools/idf_tools.py export) >> $HOME/.bashrc

COPY . /project

RUN chmod +x /project/test/entrypoint.sh

WORKDIR /project/test

ENTRYPOINT [ "/project/test/entrypoint.sh" ]
# ADD entrypoint.sh /entrypoint.sh
# RUN chmod +x /entrypoint.sh

# # USER ${CONTAINER_USER}
# # ENV USER=${CONTAINER_USER}
# # WORKDIR /home/${CONTAINER_USER}

# ENTRYPOINT [ "/entrypoint.sh" ]
# CMD ["/bin/bash", "-c"]
