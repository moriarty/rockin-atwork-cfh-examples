# rockin-atwork-cfh-examples

This repository holds standalone examples for communicating with the RoCKIn-at-Work Central Factory Hub (CFH).

The CFH code repository is located here: https://github.com/mas-group/rockin-refbox



Instructions
---

First modify src/peer.cpp, replacing the IP address with your local IP address. 

TO MAKE
---

First clone the repository, then:

    mkdir build
    cd build
    cmake ..
    make

TO TEST
---

Have the REFBOX running somewhere, either on the network or on your local machine.

From inside the build directory:

    ./peer

NOTES
---

Currently libs/protobuf_comm and protobuf/msgs are manually copied from the upstream rockin-refbox. 
They are not guarenteed to be up to date. Please ensure to check with the upstream repositories for changes before 
competitions. In the future these may be included as external CMake projects or git submodules. 


