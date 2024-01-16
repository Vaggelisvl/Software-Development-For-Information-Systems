!/bin/bash

# Check if gtest is installed
if ! dpkg -l | grep -q libgtest-dev; then
    echo "Google Test not found. Installing..."

    # Install gtest using apt (Debian-based systems)
    sudo  apt-get update
    sudo   apt-get install -y libgtest-dev

    # Build and install gtest
    cd /usr/src/gtest || exit
    sudo  cmake CMakeLists.txt
    sudo  make
    sudo  cp *.a /usr/lib

    echo "Google Test installed successfully."
else
    echo "Google Test is already installed."
fi