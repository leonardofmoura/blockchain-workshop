FROM ubuntu:24.10

ENV DEBIAN_FRONTEND=noninteractive

# Update and install dependencies
RUN apt update && apt upgrade -y

RUN apt install -y \
  cmake \
  build-essential \
  pkg-config \
  libsodium-dev

CMD ["bash"]
