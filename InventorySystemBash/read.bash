#!/bin/bash

#read.bash is the script that has the logic for reading an existing item
#user gets to print out all the information about the specified item


#prompts the user for the item number first
read -p "Enter an item number: " item_number

#if the item number doesn't already exist, will print out an error statement
if [ ! -f "./data/$item_number.item" ]; then
	echo "ERROR: item not found"
fi

#this while loop reads in the lines of the file, saving the values
#into the associated values

while true; do
	read simple_name item_name
	read current_quantity max_quantity
	read desc
	break
done <"./data/$item_number.item" 

#prints out the attributes of the existing item
echo "Item Name: $item_name"
echo "Simple Name: $simple_name"
echo "Item Number: $item_number"
echo "Qty: $current_quantity/$max_quantity"
echo "Description: $desc"
