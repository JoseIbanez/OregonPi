#!/bin/bash

cd ~/Projects/
sudo apt-get install -y git-core
sudo apt-get update -y 
sudo apt-get upgrade -y 
git clone git://git.drogon.net/wiringPi
cd wiringPi
git pull origin
./build
