#!/bin/bash

# Dirs
VENDOR_DIR="vendor/"
SDL_SOURCE_DIR="$VENDOR_DIR/SDL3"
SDL_IMAGE_SOURCE_DIR="$VENDOR_DIR/SDL3_image"

# Urls
SDL_URL="https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.2.8.zip"
SDL_IMAGE_URL="https://github.com/libsdl-org/SDL_image/archive/release-3.2.4.zip"

# Create Dirs
mkdir -p "$SDL_SOURCE_DIR"
mkdir -p "$SDL_IMAGE_SOURCE_DIR"

# Download and extract
download_and_extract() {
  local url=$1
  local dest_dir=$2
  local zip_file="${dest_dir}.zip"

  echo "Downloading $url..."
  curl -L "$url" -o "$zip_file"

  echo "Extracting $zip_file..."
  unzip -q "$zip_file" -d "$dest_dir"

  mv "$dest_dir"/*/* "$dest_dir/"
  
  rm "$zip_file"
}

# Download and extract sdl & sdl_image
download_and_extract "$SDL_URL" "$SDL_SOURCE_DIR"
download_and_extract "$SDL_IMAGE_URL" "$SDL_IMAGE_SOURCE_DIR"