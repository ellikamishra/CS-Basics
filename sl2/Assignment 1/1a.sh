#!/bin/bash

Display(){   #display function
cat $f

read -p "Enter rollno. to view result" r   #taking input for rno. to search
echo "$r"

while read -ra line; do      #reading file line wise

if (( $r == ${line[0]} ))    #if rno. is entered then print following
then
echo "----------------------------------------------------------------------------------------------------"
echo "Roll No  Name  College   Class   Div  Subject1  Subject2  Subject3  Subject4  Subject5 Average"
echo "----------------------------------------------------------------------------------------------------"
printf "\n%7d\t%4s\t %5s\t %3s\t %3d\t%3d\t%3d\t %3d\t %3d\t %3d\t %7.2f\n\n" ${line[0]}  ${line[1]}  ${line[2]}  ${line[3]} ${line[4]} ${line[5]} ${line[6]} ${line[7]} ${line[8]} ${line[9]} ${line[10]}
echo "----------------------------------------------------------------------------------------------------"
echo -e $"\nsub1 : ${line[5]}\nsub2 : ${line[6]}\nsub3 :${line[7]}\nsub4 :${line[8]}\nsub5 :${line[9]}\nAverage:${line[10]}"
 echo "----------------------------------------------------------------------------------------------------"
 if [ ${line[5]} -ge 20 ]  #print subject wise pass,fail
 then 
  echo "Pass in sub1"
 else 
  echo "Fail"
 fi
 if [ ${line[6]} -ge 20 ]
 then 
  echo "Pass in sub2"
 else 
  echo "Fail"
 fi
 if [ ${line[7]} -ge 20 ]
 then 
  echo "Pass in sub3"
 else 
  echo "Fail"
 fi
 if [ ${line[8]} -ge 20 ]
 then 
  echo "Pass in sub4"
 else 
 echo "Fail"
 fi
 if [ ${line[9]} -ge 20 ]
 then 
  echo "Pass in sub5"
 else 
  echo "Fail"
  fi
 fi
done < $1

}

Input()   #input function
{ if [ $2 == 1 ]
  then
   d=33100
   div=9
   

  elif [ $2 == 2 ]
  then
   d=33200
   div=10
   
   
  else
   d=33300
   div=11
 fi
   for(( i=1; i<=$1; i++ ))
 do
 sroll=`expr $d + $i`
 echo $sroll
while true
 do
 read -p "Enter name" sname   #take valid inputs 
 if [ -z "$sname" ]
		then 
		    echo 'Inputs cannot be blank!'
		elif [[ "$sname" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "Name should contain only alphabets"
		fi 
	  done
 while true
do	 
 read -p "Enter college" sclg
 if [ -z "$sclg" ]
		then 
		    echo 'Inputs cannot be blank!'
		elif [[ "$sclg" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "College should be alphabetic"
		
		fi 
	  done
 while true
do	  
 read -p "Enter class" class
 if [ -z "$class" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$class" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
		    echo "Class should be alphabetic"
		fi 
	  done
 
 read -p "Enter sub1 marks" s1
 read -p "Enter sub2 marks" s2
 read -p "Enter sub3 marks" s3
 read -p "Enter sub4 marks" s4
 read -p "Enter sub5 marks" s5
 t=`expr $s1 + $s2 + $s3 + $s4 + $s5`
 avg=`expr $t / 5`
 
 echo "$sroll $sname $sclg $class $div $s1 $s2 $s3 $s4 $s5 $avg ">>$f    #writing to file
 
 done
 
}

Modify(){     #modify function using grep


echo "enter rn. to modify"
 read sroll
 grep -v "$sroll" $f>>db1
 mv db1 $f
 
 while true
 do
 read -p "Enter name" sname
 if [ -z "$sname" ]
		then 
		    echo 'Inputs cannot be blank!'
		elif [[ "$sname" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "Name should contain only alphabets"
		fi 
	  done
	 
	 
while true
do	 
 read -p "Enter college" sclg
 if [ -z "$sclg" ]
		then 
		    echo 'Inputs cannot be blank!'
		elif [[ "$sclg" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "College should be alphabetic"
		
		fi 
	  done
while true
do	  
 read -p "Enter class" class
 if [ -z "$class" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$class" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
		    echo "Class should be alphabetic"
		fi 
	  done
 read -p "Enter sub1 marks" s1
 read -p "Enter sub2 marks" s2
 read -p "Enter sub3 marks" s3
 read -p "Enter sub4 marks" s4
 read -p "Enter sub5 marks" s5
 read -p "Enter division" div
 
 t=`expr $s1 + $s2 + $s3 + $s4 + $s5`
 avg=`expr $t / 5`
 
 echo "$sroll $sname $sclg $class $div $s1 $s2 $s3 $s4 $s5 $avg">>$f

}

Delete(){   #delete functon using grep

echo "enter rn. to delete"
 read sroll
 grep -v "$sroll" $f>>db1
 mv db1 $f
 cat $f

}
Search(){     #search function using grep

if ( grep -w "$1" $f ) 
then

  echo "Found record with rollno $1"

else
    "Not found record with rollno $1"
fi
}
echo "Enter file-" 
read f
c=0
while (( $c!=5 ))
do
echo "****Menu****

1.Display
2.Input
3.Modify
4.Delete
5.Search
6.Exit"

read -p "Enter choice-" c

case "$c" in
 

 
 1)Display $f;;
 2)echo "Input:"
 read -p "Enter no. of students to enter:" n 
 read -p "Enter division:" d
   Input $n $d
 
 
 ;;
 3)echo "Modify:"
 Modify
 ;;
 4)echo "Delete:"
 Delete
 ;;
 5)echo "Search:"
  read -p "Enter rollno. to search:" n 
   Search $n;;
 6)exit;;
 esac
 done
 
 
 

