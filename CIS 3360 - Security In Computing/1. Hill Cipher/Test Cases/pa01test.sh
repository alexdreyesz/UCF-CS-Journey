#!/bin/bash
case $1 in
    pa01.c)
	rm -f -- a.out
	gcc pa01.c 
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa01.c failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="./a.out"
	;;
    pa01.cpp)
	rm -f -- a.out
	g++ pa01.cpp
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa01.cpp failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="./a.out"
	;;
    pa01.go)
	rm -f -- pa01
	go build pa01.go
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa01.go failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="./pa01"
	;;
    pa01.java)
	rm -f -- pa01.class
	javac pa01.java
	if [ $? -ne 0 ]; then 
	    echo "Compile of pa01.java failed"
	    echo "Good bye!"
	    exit 1 
	fi
	EXE="java pa01"
	;;
    pa01.py)
	EXE="python3 pa01.py"
	;;
*)
    echo "Invalid source file name"
    echo "->  should be pa01.c, pa01.cpp, pa01.go, pa01.java or pa01.py"
    exit 1
esac

echo "Compile of pa01 succeded."

echo "Case #1"
eval $EXE k1.txt p1.txt >stu1Output.txt
diff -w stu1Output.txt base1.txt
echo "Case #1 - complete"

echo "Case #2"
eval $EXE k2.txt p2.txt >stu2Output.txt
diff -w stu2Output.txt base2.txt
echo "Case #2 - complete"

echo "Case #3"
eval $EXE k3.txt p3.txt >stu3Output.txt
diff -w stu3Output.txt base3.txt
echo "Case #3 - complete"

echo "Case #4"
eval $EXE k4.txt p4.txt >stu4Output.txt
diff -w stu4Output.txt base4.txt
echo "Case #4 - complete"

echo "Case #5"
eval $EXE k5.txt p5.txt >stu5Output.txt
diff -w stu5Output.txt base5.txt
echo "Case #5 - complete"
