#!/bin/bash

find /var/oregonpi/ -type f -mmin +10 -delete
/home/pi/Projects/OregonPi/getTemp /var/oregonpi/

