# Student Management System

## Overview

This C++ program implements a Student Management System that allows users to manage a list of students stored in a linked list. Each student record includes their full name, age, and score. The program provides functionalities to load, display, add, edit, remove, search, sort, and analyze student data, with the ability to save changes to a file.

## Features

The program supports the following operations:

* **Load Data**: Reads student data from a text file (`Data.txt`) with entries in the format `fullname;age;score`.
* **Display List**: Prints a formatted table of all students with index, full name, age, and score.
* **Add Student**: Appends a new student to the list with user-provided details.
* **Edit Student**: Modifies a student's full name, age, or score based on their index.
* **Remove Student**: Deletes a student from the list by index and updates subsequent indices.
* **Search by Name**: Finds and displays students whose names contain a specified substring.
* **Sort List**: Sorts the student list by name (alphabetically), age (ascending), or score (ascending).
* **Statistics**: Calculates and displays the class average score, percentages of students in different performance categories (very good, good, bad), and identifies students with the highest score.
* **Save Data**: Writes the current student list back to the file.
* **Exit**: Terminates the program.

## Techniques Used

The program employs several C++ programming techniques and concepts:

* **Linked List**: Uses a singly linked list to store student records.
* **Dynamic Memory Management**: Uses `new` and `delete` with a destructor to prevent memory leaks.
* **File I/O**: Uses `std::ifstream` and `std::ofstream` for reading/writing data.
* **Bubble Sort Algorithm**: Used for sorting based on specified criteria.
* **Enum Class**: Ensures type-safe sorting criteria.

## Usage

### Interact with the Menu

Choose options 1–9 to perform various operations. Follow prompts to input student details, indices, or search strings. Option 9 exits the program.

### Output

* The program displays results in the console (e.g., student lists, statistics).
* Changes are saved to `Data.txt` when using the save option.

### Example Output

```
Danh sach thao tac:
1 - In danh sach SV
2 - Them
3 - Sua
4 - Xoa
5 - Tim kiem
6 - Sap xep
7 - Thong ke
8 - Sao luu
9 - Thoat

Nhap lenh: 1
[1] Danh sach sinh vien:
+------+--------------------------------+--------+------------+
|STT   |Ho va ten                       |Tuoi    |Diem so     |
+------+--------------------------------+--------+------------+
|1     |Nguyen Van A                    |20      |8.5         |
|2     |Tran Thi B                      |19      |7.0         |
|3     |Le Van C                        |21      |4.5         |
+------+--------------------------------+--------+------------+
```

## Requirements

* C++ compiler (e.g., g++, clang++)
* Standard C++ library (C++11 or later)
