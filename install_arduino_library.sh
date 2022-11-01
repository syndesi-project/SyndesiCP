#!/bin/sh

./make_arduino_library.sh

rm -rf ~/Arduino/libraries/syndesicp

cp -r arduino/syndesicp ~/Arduino/libraries
