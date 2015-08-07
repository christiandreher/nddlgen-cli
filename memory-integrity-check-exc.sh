#!/bin/bash

valgrind --leak-check=yes ./Debug/nddlgen-cli -b -i /home/chris/models/nosdf.sdf
