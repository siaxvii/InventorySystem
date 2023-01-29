#!/bin/bash

#create.bash has all the logic for creating a new item
#the user can enter information about the item such as its number, simple name,
#item name, current and maximum quantities, and description.

#following block of read statements prompts user for item attributes one at a time
read -p "Item number: " item_number
read -p "Simple name: " simple_name
read -p "Item name: " item_name
read -p "Current quantity: " current_quantity
read -p "Maximum quantity: " max_quantity
read -p "Description: " desc

#this if statement ensures that the user inputted item doesn't already exist
if [ -f "./data/$item_number.item" ]; then
	echo "ERROR: item already exists"
else	#else will continue with the script, creating/appending attributes of new item

	echo "$simple_name $item_name" > "./data/$item_number.item"
	echo "$current_quantity $max_quantity" >> "./data/$item_number.item"
	echo "$desc" >> "./data/$item_number.item"
	
	#this part of the script formats the date and provides documentation
	tDate=$(date +"%Y-%m-%d %H:%M:%S")
	echo "CREATED: $tDate - $simple_name" >> ./data/queries.log
fi

