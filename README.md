# nddl-generator-cli

## General

This package is the CLI to use the nddl-generator-core library.

## Dependencies

### Compiler

#### Include paths (-l)
 * *path to sdformat-2.3*
 * *path to nddl-generator-core/src*

#### Include files (-include)
 * *none*

#### Miscellaneous
 * Other flags: *-c -fmessage-length=0 -std=c++0x*
 
### Linker

#### Libraries (-l)
 * nddl-generator-core
 * sdfformat (part of libsdfformat2-dev)
 * boost_filesystem (part of libboost-all-dev)
 * boost_system (part of libboost-all-dev)

#### Include Paths (-L)
 * *path to nddl-generator-core .a file*

## License

Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)  
  
Licensed under the Apache License, Version 2.0 (the "License");  
you may not use this file except in compliance with the License.  
You may obtain a copy of the License at  
  
[http://www.apache.org/licenses/LICENSE-2.0]()  
  
Unless required by applicable law or agreed to in writing, software  
distributed under the License is distributed on an "AS IS" BASIS,  
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
See the License for the specific language governing permissions and  
limitations under the License.
