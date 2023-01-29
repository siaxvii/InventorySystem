#!/bin/bash 

#delete.bash is a script that has the logic for deleting an item that already exists
#user can enter in the item number of the item they wish to delete
#program prints out confirmation statement that it has been deleted

#first prompts user for the item number of the item they want to delete
read -p "Enter an item number: " item_number

#if the item exists in the directory, then continue with the script
if [ -f "./data/$item_number.item" ]; then
	
	#grabs the simple name of the item before it deletes the item file
	read simple_name item_name < "./data/$item_number.item"
	rm "./data/$item_number.item"

	#documents the deleted item in queries.log in the data directory
	#and prints out confirmation that it has been deleted
	TDate=$(date +"%Y-%m-%d %H:%M:%S")	
	echo "DELETED: $TDate - $simple_name" >> ./data/queries.log
	echo "$simple_name was successfully deleted"
else
#if the user enters an item number that doesn't exist, prints out an error statement
	echo "ERROR: item not found"	
fi
