# Webserv
An http server implemented using C++98.

## Overview
 * This is a single threaded web server that was developed using I/O mutliplexing to serve concurrent clients.
 * It is implemented in C++98 using the socket api.
 * It is designed to serve static web content for small sized projects.
 * The http methods supported are : GET, POST and DELETE.
 * It supports cgi (php and python) and cookies.
 
## Setup
  * Clang should be installed. (Obviously to compile C++ code)
  * Make is optional. (if you want to use the Makefile)
  * This project was developed under a unix environment (macOS). Compiling this code without errors in any other environment is not guaranteed.

## Usage
  In your terminal, clone this repo and go to the root directory : 
  ```bash
  git clone https://github.com/oessayeg/Webserver.git && cd Webserver
  ```
  Compilation part :
    * If you have make : 
    ```bash
    make && ./webserv
    ```
    * If you don't have make :
    ```bash
    c++ srcs/*.cpp && ./webserv
    ```
