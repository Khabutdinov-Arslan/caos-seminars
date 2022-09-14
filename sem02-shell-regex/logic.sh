#!/usr/bin/bash

ping 8.800.555.3535 -c 1 || echo "8.800.555.3535 not found"
ping 8.8.8.8 -c 1  && echo "8.8.8.8 found"
