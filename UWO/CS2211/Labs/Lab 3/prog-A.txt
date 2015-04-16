#!/bin/sh
i=1
while [ $i -le 3 ]; do
  echo $0 $i ":"   `date`
  sleep 1
  i=`expr $i + 1`
done
echo $0 ": finished execution." 
