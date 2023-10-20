# RedisPubSubEventCollector

This project uses Redis pub/sub as an event controller and is implemented in both python and C++.

<font color="red">***note***</font>: Further information will be given regarding each implementation.

---
## Author

- [Helia_Ghahraman](https://github.com/helia-ghahraman)

<br>

## Get project
```bash
  git clone https://github.com/helia-ghahraman/Redis-Event-Controller.git
  cd Redis-Event-Controller
```
<br>

---
# 1) Python

<br>

## Installation

For installing the dependencies for python implementation, just run the bellow command:
```bash
pip install -r requirement.txt

```

---
<br>

## API Reference (server code)

### Import Classes And Create Objects

```python
import redis
```

### handle_message
```python
def handle_message(message):
```

| Function name   | Return type | Description                                                                  |
|:----------|:------------|:-----------------------------------------------------------------------------|
| `handle_message` | `void`      | Takes a string as an argument and considers it as the message to be printed. |


---
<br>


## API Reference (client code)

### Import Classes And Create Objects

```python
import redis
import argparse
import random
import time

r = redis.Redis(host='localhost', port=6379, db=0)
```

| Parameter        | Type                  | Description                                                        |
|:-----------------|:----------------------|:-------------------------------------------------------------------|
| `r`              | `Redis object`        | a redis object that allows us to use the redis functions.          |

<br>
<br>

---
# 2) C++


### Prerequisites

Versions of the software used can be changed to better suit the needs of the developer(s). If you wish to use the
template *as-is*, meaning using the versions recommended here, then you will need:

* **CMake v3.15+** - found at [https://cmake.org/](https://cmake.org/)

* **C++ Compiler** - needs to support at least the **C++17** standard, i.e. *MSVC*,
*GCC*, *Clang*
> ***Note:*** *You also need to be able to provide ***CMake*** a supported
[generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).*

<br>

## Installation

For installing the dependencies for C++ implementation, just run the bellow commands:
```bash
git clone --recursive https://github.com/cpp-redis/cpp_redis.git
cd cpp_redis
git submodule update --init --recursive
cd cpp_redis/build
cmake ..
make
sudo make install

```
After finishing getting a copy of the project, create a new folder in the `include/` folder, with the name of your project.  Edit
`cmake/SourcesAndHeaders.cmake` to add your files.

You will also need to rename the `cmake/ProjectConfig.cmake.in` file to start with
the ***exact name of your project***. Such as `cmake/MyNewProjectConfig.cmake.in`.
You should also make the same changes in the GitHub workflows provided, notably
[`.github/workflows/ubuntu.yml`](.github/workflows/ubuntu.yml), in which you should
replace the CMake option `-DProject_ENABLE_CODE_COVERAGE=1` to
`-DMyNewProject_ENABLE_CODE_COVERAGE=1`.

Finally, change `"Project"` from `CMakeLists.txt`, from

```cmake
project(
  "Project"
)
```

to the ***exact name of your project***, i.e. using the previous name it will become:

```cmake
project(
 RedisPubSubExample
)
```

To install an already built project, you need to run the `install` target with CMake.
For example:

```bash
cmake --build build --target install --config Release

# a more general syntax for that command is:
cmake --build <build_directory> --target install --config <desired_config>
```

## Building the project

To build the project, all you need to do, ***after correctly
[installing the project](README.md#Installing)***, is run a similar **CMake** routine
to the the one below:

```bash
mkdir build/ && cd build/
cmake .. -DCMAKE_INSTALL_PREFIX=/absolute/path/to/custom/install/directory
cmake --build . --target install
```

> ***Note:*** *The custom ``CMAKE_INSTALL_PREFIX`` can be omitted if you wish to
install in [the default install location](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html).*

More options that you can set for the project can be found in the
[`cmake/StandardSettings.cmake` file](cmake/StandardSettings.cmake). For certain
options additional configuration may be needed in their respective `*.cmake` files
(i.e. Conan needs the `CONAN_REQUIRES` and might need the `CONAN_OPTIONS` to be setup
for it work correctly; the two are set in the [`cmake/Conan.cmake` file](cmake/Conan.cmake)).


---
<br>

## API Reference (server code)

### Import Classes And Create Objects

```cpp
#include <cpp_redis/cpp_redis>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

bool new_message_received ;
cpp_redis::subscriber sub;
std::mutex new_message_mutex;
std::condition_variable new_message_cv;
```
| Parameter        | Type                  | Description                                                        |
|:-----------------|:----------------------|:-------------------------------------------------------------------|
| `new_message_received`  | `bool`        | This is a flag that indicates whether a new message has been received by the worker thread. |
| `sub`              | `subscriber object`        | An object that allows us to use the subscriber's function. |
| `new_message_mutex`     | `mutex object`        | This is a mutex (short for mutual exclusion) that provides synchronization and ensures exclusive access to shared resources.|
| `new_message_cv`        | `condition_variable`        | This is a condition variable that allows threads to wait for a certain condition to be met and get notified by another thread when that condition becomes true.   |

<br>

### worker_thread
```cpp
void worker_thread(cpp_redis::subscriber& sub) {

}
```

| Function name   | Return type | Description                                                                  |
|:----------|:------------|:-----------------------------------------------------------------------------|
| `worker_thread` | `void`      | Subscribes to the "chatroom" channel using the cpp_redis::subscriber object passed as a reference. When a message is received, it updates the received_message and new_message_received variables, unlocks the mutex, and notifies the condition variable. |


---
<br>


## API Reference (client code)

### Import Classes And Create Objects

```cpp
#include <cpp_redis/cpp_redis>
#include <iostream>
#include <chrono>
#include <random>

cpp_redis::client client;
std::random_device rd;
int sleep_duration = dis(gen);
```

| Parameter        | Type                  | Description                                                        |
|:-----------------|:----------------------|:-------------------------------------------------------------------|
| `client`              | `Redis client object`        | This is the client object used to interact with the Redis server.|
| `rd`              | `Random device object`        | This generates random numbers from hardware entropy.|
| `sleep_duration`              | ` int`        | This generates a random sleep duration between 1000 and 5000 milliseconds.|
<br>
<br>







