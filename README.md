# University Management System 

## Overview
This project is a **University Management System** implemented in **C++**. It includes various data structures like **Doubly Linked List (DLL)**, **Binary Search Tree (BST)**, **Singly Linked List (SLL)**, **Stack**, **Queue**, **Sorting & Searching algorithms**, and **Hash Table** to manage student records, course enrollments, and prerequisite validations efficiently.

## Features
- **Student Management**: Add, delete, and display student records.
- **Course Management**: Add, delete, and search for courses using a **BST**.
- **Enrollment History**: Track student course enrollments using a **DLL**.
- **Waitlist System**: Implemented with a **Queue** to handle over-enrolled courses.
- **Sorting and Searching**:
  - **Quick Sort**: Sort students and courses efficiently.
  - **Hashing**: Fast course search using a **Hash Table**.
- **Prerequisite Validation**: Ensure students meet course prerequisites using a **Stack**.

## Technologies Used
- **C++ Standard Library** (`<iostream>`, `<string>`, `<list>`, `<vector>`, `<algorithm>`)
- **Data Structures**: BST, DLL, SLL, Stack, Queue, Hash Table
- **Object-Oriented Programming (OOP)** principles

## Code Structure
```bash
.
├── System.cpp  # Main implementation file
└── README.md   # Project documentation
```

## How to Compile and Run
1. **Compile the Code**:
   ```bash
   g++ -o system System.cpp
   ```
2. **Run the Program**:
   ```bash
   ./system
   ```

## Menu Options
When you run the program, you will see the following menu:
```
--- Student Records Management ---
1. Add Student
2. Delete Student
3. Display All Students
4. Add Course to Student History
5. View Student Enrollment History
6. Add Course to System
7. Delete Course from System
8. Search Student by ID
9. Sort Students by ID
10. Search Course by ID
11. Sort Courses
12. Search using Hashing
13. Validate Course Prerequisites
14. Add a Student to the Waitlist
15. Enroll the First Student on the Waitlist
16. Display Students on the Waitlist
17. Exit
```

## Example Usage
- **Adding a Student**:
  ```
  Enter Student ID: 101
  Enter Name: John Doe
  Enter Email: john@example.com
  Enter Phone: 1234567890
  Enter Address: 123 Street, City
  Enter Password: ******
  Student added successfully.
  ```
- **Adding a Course**:
  ```
  Enter Course ID: 501
  Enter Course Name: Data Structures
  Enter Course Credits: 3
  Enter Course Instructor: Dr. Smith
  Course added successfully.
  ```

## Future Improvements
- Implement a **Graph-based** course prerequisite system
- Develop a **GUI** for better user interaction
- Integrate with a **Database** for persistent storage

## License
This project is licensed under the **MIT License**.
