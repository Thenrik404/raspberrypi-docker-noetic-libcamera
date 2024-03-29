FROM ros:noetic-ros-base-focal
# FROM ubuntu:20.04 as cpu
ARG UID=1000
ARG GID=1000
ARG VIDEOID=44
ARG GPIOID=993
ARG I2CID=994
ARG SPIID=995

LABEL maintainer "Henrik Trommer <henrik.trommer@uni-goettingen.de>"

SHELL ["/bin/bash","-c"]

## BEGIN: packages
################################################################

RUN apt update && apt install --no-install-recommends -y \
    software-properties-common 
RUN add-apt-repository universe

RUN apt update --fix-missing && apt install --no-install-recommends -y \
    wget \
    curl \
    git \
    vim \
    nano \
    tree \
    && rm -rf /var/lib/apt/lists/*

RUN apt update && sudo apt-get install -y libavdevice-dev && sudo apt-get install -y rapidjson-dev
RUN apt -y install ffmpeg libavdevice-dev gdb
RUN apt -y install pciutils zlib1g unzip mlocate python3-pyqt5

################################################################
## END: packages
## BEGIN: ros:noetic
################################################################

RUN apt update && apt install --no-install-recommends -y \
    python3-rosdep \
    python3-rosinstall \
    python3-vcstools \
    python3-catkin-tools \
    ros-noetic-cv-bridge \
    ros-noetic-tf \
    ros-noetic-wfov-camera-msgs \
    ros-noetic-image-exposure-msgs \
    ros-noetic-camera-info-manager \
    ros-noetic-image-transport \
    ros-noetic-roslint \
    ros-noetic-image-proc \
    ros-noetic-robot-state-publisher \
    ros-noetic-diagnostic-updater \
    ros-noetic-xacro


################################################################
## END: ros:noetic
## BEGIN: python packages
################################################################
RUN apt update && apt install --no-install-recommends -y \
    python3 \
    python3-pip 
RUN pip3 install numpy scipy opencv-contrib-python
RUN pip3 install rospkg rospy-message-converter
RUN pip3 install picamera2
################################################################
## END: python packages
## BEGIN: libcamera
################################################################
RUN pip3 install meson ninja jinja2 ply
RUN apt install -y libyaml-dev python3-yaml python3-ply python3-jinja2
RUN apt install -y libdw-dev libunwind-dev
RUN apt install -y libudev-dev
RUN apt install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
RUN apt install -y libpython3-dev pybind11-dev
RUN apt install -y libevent-dev libdrm-dev libjpeg-dev libsdl2-dev
RUN git clone https://github.com/raspberrypi/libcamera.git /opt/libcamera
# COPY meson_options.txt /opt/libcamera/meson_options.txt
WORKDIR /opt/libcamera
RUN meson setup build -Dcam=enabled -Dpycamera=enabled -Dpipelines=rpi/vc4,rpi/pisp
RUN sudo ninja -C build install
################################################################
## END: libcamera
## BEGIN: LCCV
################################################################
RUN apt install -y libopencv-dev
RUN git clone https://github.com/kbarni/LCCV.git /opt/LCCV
RUN mkdir /opt/LCCV/build
WORKDIR /opt/LCCV/build
RUN cmake ..
RUN sudo make install
################################################################
## END: LCCV
## BEGIN: user setup
################################################################
RUN groupadd -g $GID docker
RUN groupadd -g $GPIOID gpio
RUN useradd -rm -d /home/docker -s /bin/bash -g docker -G sudo -u $UID docker -p "$(openssl passwd -1 docker)"
RUN usermod -a -G video docker
WORKDIR /home/docker

################################################################
## END: user setup
## BEGIN: ROS
################################################################

# Create local catkin workspace
ENV CATKIN_WS=/home/docker/catkin_ws
ENV ROS_PYTHON_VERSION=3
WORKDIR $CATKIN_WS

# Initialize local catkin workspace
RUN source /opt/ros/${ROS_DISTRO}/setup.bash \
    && cd $CATKIN_WS \
    && rosdep install -y --from-paths . --ignore-src --rosdistro ${ROS_DISTRO}

RUN apt update && apt install --no-install-recommends -y \
    bash-completion \
    ros-noetic-image-pipeline \
    python3-tk

# apt cache fix
RUN rm /etc/apt/apt.conf.d/docker-clean &&\
    apt-get update

RUN touch /home/docker/.sudo_as_admin_successful

################################################################
## END: ROS
## BEGIN: Workspace
################################################################

# enable case-insensitive tab completion
RUN echo 'set completion-ignore-case On' >> /etc/inputrc

################################################################
## END: Workspace
# run this with sudo

## BEGIN: 
################################################################

WORKDIR $CATKIN_WS

COPY .bashrc /home/docker/.bashrc

# entrypoint stuff
COPY ./entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]

USER docker
