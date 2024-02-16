### Description

[Docker container](https://www.docker.com/) enabling the raspberry pi camera in ros-noetic.

Note: The system is designed to run in headless mode. In the Dockerfile, we compile libcamera
from source. Thus, if a GUI is needed one needs to modify the build instructions in the dockerfile and set the DISPLAY variable in the docker-compose.yaml


The setup was successfully tested on a raspberry pi 5 with bookworm as host system.

### Setup guide

#### Host Setup:

After flashing the rasperian OS, enable the camera usage using 
```bash
sudo raspi-config
```
and enable the camera unter interfacing options. 

(However, on bookworm there was no such setting and the camera was enabled by default.) 

[Install docker on the pi:](https://docs.docker.com/engine/install/raspberry-pi-os/)
```bash
sudo apt update && sudo apt upgrade -y
for pkg in docker.io docker-doc docker-compose podman-docker containerd runc; do sudo apt-get remove $pkg; done

# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
VERSION_CODENAME=bookworm
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

```

```bash
sudo apt-get update

sudo apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin

sudo groupadd docker
sudo usermod -aG docker $USER
```

Logout and login. To verify the docker installation run
```bash
docker run hello-world
```

#### Container setup

Note: The container builds an image for ros-noetic-base. 



#### Optional Host Preparations

You might want to add this alias to your bashrc/zshrc
```bash
sudo echo "alias dcexec=\"docker exec -it ros-noetic bash\"" >> ~/.bashrc
```




