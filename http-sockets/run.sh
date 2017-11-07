#!/usr/bin/env bash

cd sources && (
  echo "compiling source..."

  clang server.c -o server

  echo "starting server..."

  ./server
)
