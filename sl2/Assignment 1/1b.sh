Input(){   #input function

for(( i=1; i<=$1; i++ ))
 do
 eroll=$i
 echo $eroll
 while true
 do
 read -p "Enter name" ename     #take valid inputs
 if [ -z "$ename" ]
		then 
		    echo 'Inputs cannot be blank!'
		elif [[ "$ename" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "Name should contain only alphabets"
		fi 
	  done
while true
do	 
 read -p "Enter Department" dpt
 if [ -z "$dpt" ]
		then 
		    echo 'Inputs cannot be blank!'
		elif [[ "$dpt" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "Department should be alphabetic"
		
		fi 
	  done
 
while true
do	  
 read -p "Enter Designation" desg
 if [ -z "$desg" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$desg" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
		    echo "Class should be alphabetic"
		fi 
	  done 

 while true
 do 
 read -p "Enter basic salary" s1
 if [ -z "$s1" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$s1" =~ ^[0-9]+$ ]]
		then 
			break
		else
		    echo "Salary should be numeric"
		fi 
	  done 
 
 
 s2=`expr $s1 / 2`
 s3=`expr $s2 / 5`
 s4=`expr $s1 + $s2 + $s3`
 echo "$eroll $ename $dpt $desg  $s1 $s2 $s3 $s4">>$f     #writing to file
 
 done

}


Display(){     #display file

cat $f
choice=0
while(( $choice!=4 ))    #choose category to display
do

echo "****Menu****                      

1.Department wise
2.Salary wise
3.Designation
4.Exit
"

read -p "Enter choice-" c

case "$c" in

1) read -p "Enter department to dispaly" d
echo "----------------------------------------------------- "
echo "Eno. Name Dept Desgn. Basic DA HRA Gross"
echo "---------------------------------------------------------"
   grep -w "$d" $f;; 
2)read -p "Enter salary range" r
echo "----------------------------------------------------- "
echo "Eno. Name Dept Desgn. Basic DA HRA Gross"
echo "---------------------------------------------------------"
 grep -w "$r" $f;;
 
 3)read -p "Enter designation" ds
echo "----------------------------------------------------- "
echo "Eno. Name Dept Desgn. Basic DA HRA Gross"
echo "---------------------------------------------------------"
grep -w "$ds" $f;;

4)exit;;
esac
done

}



Modify()
{
echo "enter en. to modify"     #modify using grep
 read eroll
 grep -v "$eroll" $f>>db1
 mv db1 $f
read -p "Enter eno." eroll
 echo $eroll
 while true
 do
 read -p "Enter name" ename
 if [ -z "$ename" ]
		then 
		    echo 'Inputs cannot be blank!'
		elif [[ "$ename" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "Name should contain only alphabets"
		fi 
	  done
while true
do	 
 read -p "Enter Department" dpt
 if [ -z "$dpt" ]
		then 
		    echo 'Inputs cannot be blank!'
		elif [[ "$dpt" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
			echo "Department should be alphabetic"
		
		fi 
	  done
 
while true
do	  
 read -p "Enter Designation" desg
 if [ -z "$desg" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$desg" =~ ^[a-zA-Z]+$ ]]
		then 
			break
		else
		    echo "Class should be alphabetic"
		fi 
	  done 

 
 while true
 do 
 read -p "Enter basic salary" s1
 if [ -z "$s1" ]
		then 
		    echo 'Inputs cannot be blank please try again!'
		elif [[ "$s1" =~ ^[0-9]+$ ]]
		then 
			break
		else
		    echo "Salary should be numeric"
		fi 
	  done 
 s2=`expr $s1 / 2`
 s3=`expr $s2 / 5`
 s4=`expr $s1 + $s2 + $s3`
 echo "$eroll $ename $dpt $desg  $s1 $s2 $s3 $s4">>$f
}

Delete()                                       #delete using grep
{
echo "enter rn. to delete"
 read eroll
 grep -v "$eroll" $f>>db1
 mv db1 $f
 cat $f
}

Search()                                       #search using grep
{
if ( grep -w "$1" $f ) 
then

  echo "Found record with eno $1"

else
   echo   "Not found record with eno $1"
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
 read -p "Enter no. of employees to enter:" n 
 
   Input $n 
 
 
 ;;
 3)echo "Modify:"
 Modify
 ;;
 4)echo "Delete:"
 Delete;;
 
 5)echo "Search:"
  read -p "Enter eno. to search:" n 
   Search $n;;
 6)exit;;
 esac
 done
 
 

