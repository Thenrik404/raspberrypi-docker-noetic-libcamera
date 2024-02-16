Description

[Docker](https://www.docker.com/) container enabling the raspberry pi camera in ros-noetic.

The setup was tested on a raspberry pi 5 with bookworm as host system.

Setup guide

Host system:

After flashing the rasperian OS, enable the camera usage using 
```bash
sudo raspi-config
```
and enable the camera unter interfacing options. 

(However, on bookworm there was no such setting and the camera was enabled by default.) 

To install docker on the pi I use [these steps]()
```bash
sudo apt update && sudo apt upgrade
for pkg in docker.io docker-doc docker-compose podman-docker containerd runc; do sudo apt-get remove $pkg; done

# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -y -m 0755 -d /etc/apt/keyrings
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

Optional Host Preparations

You might want to add this alias to your bashrc/zshrc
```bash
sudo echo "alias dcexec=\"docker exec -it ros-noetic bash\"" >> ~/.bashrc
```




