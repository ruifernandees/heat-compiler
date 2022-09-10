#!/bin/bash

make clean
make test
./dist/test.out ./src/mocks/hello-world.rb
./dist/test.out ./src/mocks/unrecognized-character.rb