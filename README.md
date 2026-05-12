# Student Records Manager

A console-based C++ student record management system built as an early learning milestone while practicing core C++ concepts.

This project allows users to add, search, update, delete, display, save, and load student records using a menu-driven interface. It was created as a practice project to strengthen understanding of classes, vectors, input handling, file I/O, and basic data management in C++.

## Features

- Add new student records
- Search records by:
  - ID
  - First name
  - Last name
  - Age
  - Grade
  - Grade and division
- Update student information by ID
- Delete records by:
  - ID
  - First name
  - Last name
  - Age
  - Grade
- Display all stored records
- Save records to a CSV file
- Load records from a CSV file
- Uses Windows file dialogs for selecting save/load locations

## Technologies Used

- C++
- Standard Template Library:
  - `vector`
  - `string`
  - `optional`
  - `fstream`
  - `sstream`
- Windows API:
  - `windows.h`
  - `commdlg.h`

## What I Practiced

This project helped me practice and understand:

- Object-oriented programming in C++
- Creating and using classes
- Working with vectors
- Menu-driven program flow
- Input validation
- Searching and filtering data
- Updating and deleting records
- File handling using CSV
- Basic use of Windows file dialogs
- Managing program state across multiple menus

## Project Status

This project has reached the milestone I originally set for it.

It is not intended to be a polished production-ready application. It was built as a learning project, and I have since moved on to more advanced projects.

Further refinement would have diminishing returns, so this repository is being kept as a record of my early C++ learning progress.

## Limitations

- The program is Windows-only because it uses Windows-specific file dialog APIs.
- Names and divisions cannot contain commas because records are saved in CSV format.
- The interface is console-based.
- CSV parsing is intentionally simple.
- The project prioritizes learning over production-level architecture.

## How to Run

1. Open the project in Visual Studio.
2. Make sure the project is configured for C++.
3. Build the project.
4. Run the executable.
5. Use the console menu to manage student records.

# IMPORTANT:
For the project to run properly, it needs Multi-byte character set instead of Unicode character set (See Line 397)
How to do that: Project → Properties → Advanced → Character Set → change to "Use Multi-Byte Character Set"

## CSV Format

Saved files use the following format:

```csv
ID,FirstName,LastName,Age,Grade,Division