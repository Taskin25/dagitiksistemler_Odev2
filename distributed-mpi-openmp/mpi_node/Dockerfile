FROM ubuntu:20.04

# Çalışma dizini
WORKDIR /shared

# Paket güncellemelerini yap
RUN apt-get update && apt-get install -y \
    build-essential \
    mpich \
    openssh-server \
    sshpass \
    iputils-ping \
    vim \
    openmpi-bin \
    libopenmpi-dev

# Dosyayı mpi_node/ dizininden konteynıra kopyala
COPY mpi_node/ssh_config.sh /ssh_config.sh

# Dosya izinlerini değiştir
RUN chmod +x /ssh_config.sh

# Konteyner çalışırken aktif tutmak için bir komut
CMD ["tail", "-f", "/dev/null"]
