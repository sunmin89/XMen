# dhrystone
dhrystone 2.2 without warnings

The dhrystone v2.2 downloaded from [https://github.com/Keith-S-Thompson/dhrystone/](https://github.com/Keith-S-Thompson/dhrystone/) gives warnings at compile time.
Since this is annoying, I modified the notation and so on so as not to change the meaning of the program so that warnings did not appear.

## 在p550 RockOS上面编译和运行


```
#编译
make

#测试
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

#dhrystone的测试结果取平均值
```