#!/bin/bash
begin=0
while [ $begin -le 12 ]
do

  cid=`expr $begin % 4`
  echo "####################"
  echo begin=$begin,cid=$cid
  echo "####################"
  time taskset -c $cid ./dry2nr 20000000
  ((begin++))
done
