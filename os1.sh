#!/bin/bash

create_book(){
	echo -n "Enter name of your Address book:"
	read name
	if [ -f "$name.txt" ]; then
		echo "Already exists"
	else
		touch "$name.txt"
		echo "Address book  created successfully."
	fi
}

view_book(){
	if [ ! -s "$name.txt" ]; then
		echo "Empty"
	else
		echo "Address book:"
		cat "$name.txt"
	fi
}

insert_book(){
	echo "enter name to insert"
	read user
	echo "enter number"
	read number

	echo "$user | $number" >> "$name.txt"
}

delete_book(){
	if [ ! -s "$name.txt" ]; then
		echo "Book is empty"
	else
		echo "Enter name to delete"
	        read user
		grep -v "^$user |" "$name.txt" > temp.txt && mv temp.txt "$name.txt"
		echo "Deleted"
	fi
}

modify_book(){
	if [ ! -s "$name.txt" ]; then
		echo "Emtpy"
	else
		echo "enter name to modify"
	        read user

		grep -v "^$user |" "$name.txt" > temp.txt && mv temp.txt "$name.txt"
		insert_book
	fi
}

while true; do
	echo "Choose options"
	echo "1] Create address book"
	echo "2] View address book"
	echo "3] Insert a record"
	echo "4] Delete record"
	echo "5] Modify record"
	echo "6] Exit"

	read choice

	case "$choice" in
		1) create_book ;;
		2) view_book ;;
		3) insert_book ;;
		4) delete_book ;;
		5) modify_book ;;
		6)
			echo "Exiting"
			exit ;;
		*) echo "Invalid option" ;;
	esac
done
