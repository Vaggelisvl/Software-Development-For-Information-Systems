#!/bin/bash

if ! command -v g++-11 &> /dev/null; then
    echo "g++-11 not found. Installing..."

    # Install g++-11 using apt (Debian-based systems)
    sudo  apt-get update
    sudo  apt-get install -y g++-11

    echo "g++-11 installed successfully."
else
    echo "g++-11 is already installed."
fi