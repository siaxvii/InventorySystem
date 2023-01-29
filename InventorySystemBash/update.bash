#!/bin/bash

#update.bash is the script that has the logic for updating info of an existing item
#user can update the names, quantities and description of the existing item

count=0

#prompts the user to enter an item number
read -p "Item number: " item_number

#if statement ensures that the item number already exists, otherwise prints out error
if [ ! -r "./data/$item_number.item" ]; then
        echo "ERROR: item not found"
	exit 1
fi

#following block of read statements reads in each attribute that the user inputs
#in order to update the information about that item, or keeps it the same if left blank
read -p "Simple name: " simple_name
read -p "Item name: " item_name
read -p "Current quantity: " current_quantity
read -p "Maximum quantity: " max_quantity
read -p "Description: " desc

#this while loop reads in the values on multiple lines of the file
#and saves them in their respective variables
while true; do
	read fsimple_name fitem_name
	read fcurrent_quantity fmax_quantity
	read fdesc
	break
done <"./data/$item_number.item"

#following series of if statements checks to see if the user inputted attribute
#is the same as the attribute that already exists for the item, increments count if so
	if [ simple_name!=fsimple_name ]; then
		fsimple_name=$simple_name
		count+=1
	fi
	if [ item_name!=fitem_name ]; then
		fitem_name=$item_name
		count+=1
	fi
	if [ current_quantity!=fcurrent_quantity ]; then
		fcurrent_quantity=$current_quantity
		count+=1
	fi
	if [ max_quantity!=fmax_quantity ]; then
		fmax_quantity=$max_quantity
		count+=1
	fi
	if [ desc!=fdesc ]; then
		fdesc=$desc
		count+=1
	fi
	
	#following course of echo statements actually updates
	#the values of the variables of the item
	echo "$simple_name $item_name" > "./data/$item_number.item"
	echo "$current_quantity $max_quantity" >> "./data/$item_number.item"
	echo "$desc" >> "./data/$item_number.item"


	#following section of the script formats the date
	#and gives us documentation and history of whether it has updated the item
	TDate=$(date +"%Y-%m-%d %H:%M:%S")	
	if [ count != 0 ]; then
		echo "UPDATED: $TDate - $simple_name" >> ./data/queries.log
	fi


