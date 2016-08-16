# eternity library

c++ game framework

## posix

### project

    $ ./manage/posix/prepare.sh 

### example:core

    $ ./manage/posix/run.sh HelloCore
    [ 60%] Built target Core
    Scanning dependencies of target HelloCore
    [ 80%] Building CXX object src/Examples/CMakeFiles/HelloCore.dir/HelloCore/Main.cpp.o
    [100%] Linking CXX executable HelloCore
    [100%] Built target HelloCore
    [ 60%] Built target Core
    [100%] Built target HelloCore
    {"a":1,"b":2}
    {"num":99}
    Hello
    [100%] Built target run_HelloCore

### example:boost asio

    $ ./manage/posix/run.sh HelloBoost &
    [1] 11456
    [ 60%] Built target Core
    [100%] Built target HelloBoost
    [ 60%] Built target Core
    [100%] Built target HelloBoost

    $ telnet localhost 5000
    Trying 127.0.0.1...
    Connected to localhost.
    Escape character is '^]'.
    hello
    read 5:hello

    ^]
    telnet> Connection closed.
    error:End of file
