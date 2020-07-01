#!/bin/sh

# Install SFML3D templates for Xcode 4 into /Library/Developer/Xcode/Templates/

mkdir -p /Library/Developer/Xcode/Templates/
cp -R "$(dirname $0)/SFML3D" /Library/Developer/Xcode/Templates/
