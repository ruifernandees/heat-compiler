#!/bin/bash

echo "Compilando..."
make clean > trash.log 2>&1
make test > trash.log 2>&1
./dist/test.out ./src/mocks/hello-world.rb
./dist/test.out ./src/mocks/unrecognized-character.rb