#!/bin/bash

valgrind --leak-check=full --show-reachable=yes ./Debug/nddlgen-cli -xf --in-sdf /home/chris/models/test.sdf --in-isd /home/chris/models/test.isd
