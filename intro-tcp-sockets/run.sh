#!/usr/bin/env bash

cd sources && (
  echo "compiling source..."

  clang tcp_client.c -o tcp_client
  clang tcp_server.c -o tcp_server

  echo "spawning client and server..."

  SERVER_START="clear && echo \"starting server..\" && ./tcp_server"
  CLIENT_START="clear && echo \"starting client...\" && sleep 1 && ./tcp_client"

  ( ttab "$SERVER_START" ) &
  ( ttab "$CLIENT_START" )
)
