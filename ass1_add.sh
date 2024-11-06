#!/bin/sh

calculate_percentage_and_result() {
    dbname="$1"
    echo "Roll No | Name | M1 | M2 | M3 | Percentage | Result"
    tail -n +2 "$dbname.db" | while IFS="|" read -r rn nm m1 m2 m3; do
        total=$(($m1 + $m2 + $m3))
        percentage=$(echo "scale=2; $total / 3" | bc)
        if [ $(echo "$percentage >= 35" | bc) -eq 1 ]; then
            result="Pass"
        else
            result="Fail"
        fi
        echo "$rn | $nm | $m1 | $m2 | $m3 | $percentage | $result"
    done
}

while true; do
    echo "
    *-----------MENU-----------*
    1. Create Database
    2. Add to Database
    3. View Database
    4. Insert Into Database
    5. Delete from Database
    6. Display Result
    7. Exit
    Enter your option: \c
    *-------------------------*"
    read choice
    case "$choice" in
        1)
            echo "Enter the name of database: "
            read dbname
            touch "$dbname.db"
            echo "Roll No | Name | M1 | M2 | M3" > "$dbname.db"
            echo "Database '$dbname.db' created."
            ;;
        2)
            echo "Enter roll number of student: "
            read rn
            echo "Enter name of student: "
            read nm
            echo "Enter marks in M1: "
            read m1
            echo "Enter marks in M2: "
            read m2
            echo "Enter marks in M3: "
            read m3
            record="$rn|$nm|$m1|$m2|$m3"
            echo $record >> "$dbname.db"
            echo "Record added to '$dbname.db'."
            ;;
        3)
            echo "Enter the name of database to view: "
            read dbname
            if [ -f "$dbname.db" ]; then
                cat "$dbname.db"
            else
                echo "Database '$dbname.db' does not exist."
            fi
            ;;
        4)
            echo "Enter the name of database: "
            read dbname
            echo "Enter roll number of student to insert: "
            read rn
            echo "Enter name of student: "
            read nm
            echo "Enter marks in M1: "
            read m1
            echo "Enter marks in M2: "
            read m2
            echo "Enter marks in M3: "
            read m3
            record="$rn|$nm|$m1|$m2|$m3"
            echo $record >> "$dbname.db"
            echo "Record inserted into '$dbname.db'."
            ;;
        5)
            echo "Enter the name of database: "
            read dbname
            echo "Enter roll number of student to delete: "
            read rn
            if [ -f "$dbname.db" ]; then
                grep -v "^$rn|" "$dbname.db" > temp.db && mv temp.db "$dbname.db"
                echo "Record with roll number '$rn' deleted from '$dbname.db'."
            else
                echo "Database '$dbname.db' does not exist."
            fi
            ;;
        6)
            echo "Enter the name of database to display: "
            read dbname
            if [ -f "$dbname.db" ]; then
                calculate_percentage_and_result "$dbname"
            else
                echo "Database '$dbname.db' does not exist."
            fi
            ;;
        7)
            exit 0
            ;;
        *)
            echo "Invalid Option"
            ;;
    esac
done

