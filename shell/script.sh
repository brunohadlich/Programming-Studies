#! /bin/bash

#echo "hello bash script" > hello.txt
#echo "Write a message to be written in file my_message.txt"
#cat > my_message.txt
#echo "Now append a message to my_message.txt"
#cat >> my_message.txt
#single line comment
: '
multiline
comment
'
#print multine text
cat << whateverNameYouWant
just
a
multine text
whateverNameYouWant

count=10
#equals comparison
if [ $count -eq 9 ]
then
	echo "10 = 9 is true"
else
	echo "10 = 9 is false"
fi
#not equals comparison
if [ $count -ne 9 ]
then
	echo "10 != 9 is true"
else
	echo "10 != 9 is false"
fi
#not equals comparison
if (( $count != 1 ))
then
	echo "asd"
fi
#greater than comparison
if (( $count > 10 ))
then
	echo "10 > 10 is true"
elif (( $count < 10 )) #less than comparison
then
	echo "10 < 10 is true"
else
	echo "10 = 10  is true"
fi

age=18

if [ "$age" -lt 18 ] #less than comparison
then
	echo "18 years old required"
fi

#and example
if [ "$age" -gt 18 -a "$age" -lt 40 ]
then
	echo "Age is correct"
else
	echo "Age is not correct"
fi

age=13
if [ "$age" -lt 18 -o "$age" -gt 40 ]
then
	echo "13 < 18 or 13 > 40"
fi

index=0

while [ $index -lt 10 ]
do
	echo "$index < 10"
	index=$(( index+1 ))
done
echo "Reached 10"

index=10
until [ $index -eq 0 ]
do
	echo "$index > 0"
	index=$(( index-1 ))
done
echo "Reached 0"
#print 1, 3, 4, 7, 8, 23
for i in 1 3 4 7 8 23
do
	echo "$i"
done
#print from 3 to 14 incrementing by 1
for i in {3..14}
do
	echo "$i"
done
#print from 0 to 10 incrementing by 2
for i in {0..10..2}
do
	echo "$i"
done
value=13
for (( i = 0; i < $value; i++ ))
do
	if [ $i -lt 4 ]
	then
		continue
	fi
	if [ $i -eq 10 ]
	then
		break
	fi
	echo "$i" 
done
echo $0 "$1"
args=("$@")
echo ${args[0]} ${args[1]}
echo $@
echo ${args}
echo $#
length=$#
while read line
do
	echo "$line"
#read from file defined at first argument
#or use the default value, /dev/stdin
done < "${1:-/dev/stdin}"

#redirects ls command output to ls_stdout.txt
#and ls_stderr.txt
ls +al 1>ls_stdout.txt 2>ls_stderr.txt

ls +al >ls_stdout_stderr.txt 2>&1
ls +al >& ls_stdout_stderr.txt #same as previous line

echo "enter first string"
read st1

echo "enter second string"
read st2

if [ "$st1" == "$st2" ]
then
	echo "Strings match"
elif [ "$st1" \< "$st2" ]
then
	echo "$st1 < $st2"
elif [ "$st1" \> "$st2" ]
then
	echo "$st1 > $st2"
fi

concatenation=$st1$st2
echo $concatenation
echo ${st1^} #Capitalize first letter
echo ${st1^^} #Capitalize all letters

n1=4
n2=7

echo $(( n1 + n2 ))
echo $(expr $n1 + $n2 )
