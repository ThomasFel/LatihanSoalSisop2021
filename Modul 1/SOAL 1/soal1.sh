#!/bin/bash

if [ $(($# % 2)) -ne 0 ]
then
     res=0

     for arg in $*
     do
        (( res += arg ))
     done
     echo "Output: $res"
else
     echo "Output: Anda belum beruntung, coba lagi."
fi
