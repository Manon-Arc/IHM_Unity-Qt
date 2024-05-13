# IHM QT Client :

This repository contains the QT client of the [IHM project](https://github.com/Manon-Arc/projetDev_IHM).

## 📌 Table of Contents :

<!-- TOC -->
* [IHM QT Client :](#ihm-qt-client-)
  * [📌 Table of Contents :](#-table-of-contents-)
  * [🎯 Badges :](#-badges-)
  * [🔧 Prerequisites :](#-prerequisites-)
  * [💻 How to Install the Project :](#-how-to-install-the-project-)
    * [0. Prerequisites :](#0-prerequisites-)
    * [1. Installation :](#1-installation-)
    * [2. Lauch :](#2-lauch-)
<!-- TOC -->

## 🎯 Badges :

[![C++ logo](https://img.shields.io/badge/Language-C++-pink)](https://learn.microsoft.com/fr-fr/cpp/?view=msvc-170)
[![Qt logo](https://img.shields.io/badge/Software-Qt-green)](https://www.qt.io)

## 🔧 Prerequisites :

- [Qt6](https://www.qt.io/download) installed on your system.
- [Git](https://git-scm.com/downloads) installed on your system.
- [CMake](https://cmake.org/download/) installed on your system.
- [gRPC](https://grpc.io/docs/languages/cpp/quickstart/) installed on your system.
    - You can follow the [Build from source](https://github.com/grpc/grpc/blob/master/BUILDING.md) for any platform (
      windows included).
- [libsodium](https://libsodium.gitbook.io/doc/installation) installed on your system.

## 💻 How to Install the Project :

### 1. Installation :

- Clone the repo with the following command :
    ```bash
    git clone https://github.com/Manon-Arc/IHM_Unity-Qt.git
    ```

- Go to folder :
    ```bash
    cd IHM_Unity-Qt/
    ```

- Create a .env file :
    ```bash
    touch .env
    ``` 
    - Edit and add the following lines in the .env file :
        ```bash
        DB_PATH=<path_to_db>
        ```
        - Replace <path_to_db> with the path to the database file.
        - Example :
          ```bash
          DB_PATH=/home/user/Documents/IHM_Unity-Qt/db.sqlite
          ```
          - To build your own db file, you can use the [script_db.sql](./script_db.sql) file (WORK ONLY ON SQLITE)
    - To the db exemple, the database file is located in source folder.
      ```bash
        DB_PATH=../db
        ```
- Create a build folder :
    ```bash
    mkdir build && cd build
    ```
- Generate the project with CMake :
    ```bash
    cmake ..
    ```
- Build the project :
    ```bash
    make
    ```
- Run the project :
    ```bash
    ./IHM
    ```
    - If you want to install the project, you can run :
      ```bash
      sudo make install #On Linux
      make install #On Windows
      ```

### 2. Lauch :

- Run the project :
    ```bash
    ./IHM
    ```
