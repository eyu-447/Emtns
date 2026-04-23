#!/bin/bash
echo "Installing dependencies..."
sudo apt update && sudo apt install -y gcc libexif-dev pkg-config
echo "Compiling emtns..."
gcc src/main.c src/parser.c src/display.c -I./include $(pkg-config --cflags --libs libexif) -o emtns
sudo cp emtns /usr/local/bin/
echo "Done! You can now use 'emtns' command."