#!/usr/bin/sh

build()
{
    cd build
    cmake ../src
    cmake --build .
    if [ $? = 0 ] 
    then
        echo "Build success!"
    fi
}

clean()
{
    cd build
    rm -rf ./*
    echo "Clean success!"
}

cleanlog()
{
    cd log
    rm -rf ./* 
    echo "Clean log success!"
}

if [ $1 = "clean" ]
then
    clean
elif [ $1 = "cleanlog" ]
then
    cleanlog
elif [ $1 = "build" ]
then
    build
fi
