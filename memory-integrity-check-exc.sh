#!/bin/bash

valgrind --leak-check=yes ./Debug/nddlgen-cli -xf --in-sdf /home/chris/models/nosdf.sdf --in-isd /home/chris/models/test.isd
