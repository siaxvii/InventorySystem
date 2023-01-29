#!/bin/bash
#This main bash file is initially invoked to prompt the user with menu options that loops
#through until the user enters CTRL-D to exit

#following block of echo statements present the user with the menu before the main
#while loop starts

	echo "Enter one of the following actions or press CTRL-D to exit."
        echo "C - create a new item"
        echo "R - read an existing item"
        echo "U - update an existing item"
        echo "D - delete an existing item"

#start while loop
while read line; do

	case "$line" in
		[Cc])	#in the case that the user decides to create a new item
			bash ./create.bash
			;;

		[Rr])	#in the case that the user decides to read an existing item
			bash ./read.bash
			;;
		[Uu])	#in the case that the user decides to update an existing item
			bash ./update.bash
			;;
		[Dd])	#in the case that the user decides to delete an existing item
			bash ./delete.bash
			;;
		*)	#in the case that the user enters the wrong character
			echo "ERROR: invalid option"
			;;
	
		
	esac    
#prompts the user after each character option is selected, at the end of the while
echo "Enter one of the following actions or press CTRL-D to exit."
echo "C - create a new item"
echo "R - read an existing item"
echo "U - update an existing item"
echo "D - delete an existing item"

done
