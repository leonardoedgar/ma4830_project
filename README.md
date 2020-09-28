# ma4830_project
![Actions Status](https://github.com/leonardoedgar/ma4830_project/workflows/Continuous%20Integration%20(CI)/badge.svg)

NTU MA4830 Realtime Software Project AY20/21
* Obtain all collision-free mortar's launch configurations given a target and an obstacle. 

Owner: Leonardo Edgar (leonardo_edgar98@outlook.com)

## Table of Contents

   1. [Getting started](#markdown-header-1-getting-started)
   2. [Prerequisites](#markdown-header-2-prerequisites)
   3. [Installing](#markdown-header-3-installing)
   4. [Run](#markdown-header-4-run)
   5. [Acknowledgments](#markdown-header-5-acknowledgments)

## 1. Getting started

Welcome to **MA4830 Realtime Software** project! There are just a few steps to get you started with developing!

## 2. Prerequisites

1. Compute
    * Any computer
2. Software package (for non-docker user)
    * gcc >= 7.5.0
    * CMake >= 3.18.1

## 3. Installing

* To build the development docker image
```bash
cd dockerfiles
./update-sourcecode.sh
docker-compose -f docker-compose-dev.yaml build
```

## 4. Run

* To run the executable (using docker image)
```bash
cd dockerfiles
docker-compose run main
docker-compose down
```

* To run the executable (without docker image)
```bash
mkdir build
cd build && cmake ..
make all
./src/main
```

* To run all tests (using docker image)
```bash
cd dockerfiles
docker-compose up test
docker-compose down
```

* To run all tests (without docker image)
```bash
mkdir build
cd build && cmake ..
make all
./src/run_unit_tests
```

## 5. Acknowledgments

Great thanks to people who have worked or helped on this project

* [Tao Shuailin](https://github.com/MENGH1)
