#include <iostream>
#include <string>
#include<list>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

//****************************DLL*****************************************************
class EnrollmentStudentNode {
public:
    string courseName; // Course name
    EnrollmentStudentNode* prev; // Previous node
    EnrollmentStudentNode* next; // Next node

    // Constructor
    EnrollmentStudentNode(const string& course)
        : courseName(course), prev(nullptr), next(nullptr) {
    }
};

class EnrollmentHistory {
private:
    EnrollmentStudentNode* head;
    EnrollmentStudentNode* tail;

public:
    // Constructor
    EnrollmentHistory() : head(nullptr), tail(nullptr) {}

    // Destructor to free memory
    ~EnrollmentHistory() {
        clearHistory();
    }

    // Add a new enrollment record
    void addRecord(const string& courseName) {
        EnrollmentStudentNode* newNode = new EnrollmentStudentNode(courseName);

        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        cout << "Course \"" << courseName << "\" added to enrollment history." << endl;
    }

    // View enrollment history
    void viewHistory() const {
        if (!head) {
            cout << "No enrollment history available." << endl;
            return;
        }

        cout << "Enrollment History:" << endl;
        EnrollmentStudentNode* current = head;
        while (current) {
            cout << "- " << current->courseName << endl;
            current = current->next;
        }
    }

    // Clear the entire history
    void clearHistory() {
        while (head) {
            EnrollmentStudentNode* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    bool findCoures(const string& c) {
        EnrollmentStudentNode* temp = head; // Initialize temp to the head of the list
        while (temp != nullptr) { // Traverse the list
            if (temp->courseName == c) {
                return true; // Course found
            }
            temp = temp->next; // Move to the next node
        }
        return false; // Course not found
    }

};
// ************************************BST**********************************************
class node {
private:
    struct courseData {
        int courseId;
        string courseName;
        int courseCredits;
        string courseInstructor;
    };
    courseData data;
    node* Right;
    node* Left;
public:
    node(int id, string name, int credits, string instructor) {
        data.courseId = id;
        data.courseName = name;
        data.courseCredits = credits; // Initialize courseCredits
        data.courseInstructor = instructor;
        Right = NULL;
        Left = NULL;
    }

    courseData get_data() const { return data; }

    int get_courseId() const {
        return data.courseId;
    }
    void set_courseId(int id) {
        data.courseId = id;
    }

    int get_CourseCredits() const { return data.courseCredits; }
    void set_CourseCredits(int c) { data.courseCredits = c; }

    string get_CourseName() const { return data.courseName; }
    void set_CourseName(string s) { data.courseName = s; }

    string get_CourseInstructor() const { return data.courseInstructor; }
    void set_CourseInstructor(string s) { data.courseInstructor = s; }

    node*& get_right() { return Right; }
    const node* get_right() const { return Right; } // Const version

    void set_right(node* r) { Right = r; }

    node*& get_left() { return Left; }
    const node* get_left() const { return Left; } // Const version

    void set_left(node* l) { Left = l; }
};

class BST {
private:
    node* root;
    int size;

    void traverseAndAddCourseIds(node* current, list<int>& ids) {
        if (current == NULL)
            return;
        traverseAndAddCourseIds(current->get_left(), ids);
        ids.push_back(current->get_courseId());
        traverseAndAddCourseIds(current->get_right(), ids);
    }

public:
    BST() { root = NULL;size = 0; }

    node*& get_root() { return root; }
    const node* get_root() const { return root; } // Const version
    int get_size() { return size; }

    void addCourse(node*& root, int id, string name, int credits, string instructor) {
        node* n = new node(id, name, credits, instructor);
        if (root == NULL) {
            root = n;
            size++;
            return;
        }
        if (id > root->get_courseId()) {
            addCourse(root->get_right(), id, name, credits, instructor);
        }
        else {
            addCourse(root->get_left(), id, name, credits, instructor);
        }
    }

    node* minId(node* root) {
        if (!root->get_left()) return root;
        return minId(root->get_left());
    }

    bool dropCourse(node*& root, int id) {
        if (root == NULL) return false; // Course not found

        if (id < root->get_courseId()) {
            return dropCourse(root->get_left(), id);
        }
        else if (id > root->get_courseId()) {
            return dropCourse(root->get_right(), id);
        }
        else {
            // Course found
            if (root->get_left() == NULL && root->get_right() == NULL) {
                delete root;
                size--;
                root = NULL;
            }
            else if (root->get_left() == NULL) {
                node* temp = root->get_right();
                delete root;
                size--;
                root = temp;
            }
            else if (root->get_right() == NULL) {
                node* temp = root->get_left();
                delete root;
                size--;
                root = temp;
            }
            else {
                node* n = minId(root->get_right());
                root->set_courseId(n->get_courseId());
                root->set_CourseName(n->get_CourseName());
                root->set_CourseCredits(n->get_CourseCredits());
                root->set_CourseInstructor(n->get_CourseInstructor());
                dropCourse(root->get_right(), n->get_courseId());
            }
            return true; // Course deleted successfully
        }
    }
    // Helper function to print all courses with a given ID
    void printCoursesById(const node* root, int id) const {
        if (root == NULL) return;

        // Process the left subtree
        printCoursesById(root->get_left(), id);

        // Process the current node only if the ID matches
        if (root->get_courseId() == id) {
            cout << "Course ID: " << root->get_courseId() << ", Name: " << root->get_CourseName()
                << ", Credits: " << root->get_CourseCredits() << ", Instructor: " << root->get_CourseInstructor() << endl;
        }

        // Process the right subtree
        printCoursesById(root->get_right(), id);
    }


    string search(const node* root, int v) const {
        if (root == NULL) { return ""; }
        if (root->get_data().courseId == v) { return root->get_data().courseName; }
        if (root->get_data().courseId > v) { return search(root->get_left(), v); }
        if (root->get_data().courseId < v) { return search(root->get_right(), v); }
        return "";
    }

    void inorder(const node* root) const {
        if (root == NULL)
            return;
        inorder(root->get_left());
        cout << root->get_courseId() << " " << root->get_CourseName() << " " << root->get_CourseCredits() << " " << root->get_CourseInstructor() << endl;
        inorder(root->get_right());
    }

    list<int> courseIdList() {
        list<int> ids;
        traverseAndAddCourseIds(root, ids);
        return ids;
    }
};

// *******************************SLL**************************************************************
class Student {
public:
    int id;
    string name, email, phone, address, password;
    EnrollmentHistory history; // Link to the student's enrollment history
    Student* next;

    Student(int i, const string& n, const string& e, const string& p, const string& a, const string& pass)
        : id(i), name(n), email(e), phone(p), address(a), password(pass), next(nullptr) {
    }
    void display() const {
        cout << "Student ID: " << id << ", Name: " << name << endl;
    }
};

class SLL {
private:
    Student* head;

public:
    SLL() : head(nullptr) {}

    // Function to add a student to the list
    void addStudent() {
        int id;
        string name, email, phone, address, password;

        cout << "Enter Student ID: ";
        while (!(cin >> id)) {
            cout << "Invalid input. Please enter a valid numeric ID: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Password: ";
        getline(cin, password);

        Student* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Student with this ID already exists." << endl;
                return;
            }
            temp = temp->next;
        }

        Student* newStudent = new Student(id, name, email, phone, address, password);
        if (!head) {
            head = newStudent;
        }
        else {
            temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newStudent;
        }
        cout << "Student added successfully." << endl;
    }

    void printStudentList() const {
        Student* current = head;
        if (!current) {
            cout << "No students to display." << endl;
            return;
        }
        while (current != nullptr) {
            current->display();
            current = current->next;
        }
    }

    // Function to search a student by ID
    Student* searchStudentById(int id) {
        Student* temp = head;
        while (temp) {
            if (temp->id == id) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Function to display all students
    void displayStudents() const {
        if (!head) {
            cout << "No students." << endl;
            return;
        }
        Student* temp = head;
        while (temp) {
            cout << "ID: " << temp->id << ", Name: " << temp->name
                << ", Email: " << temp->email << ", Phone: " << temp->phone
                << ", Address: " << temp->address << endl;
            temp = temp->next;
        }
    }

    void displayStudentInfo(int ID) {
        if (!head) {
            cout << "No students." << endl;
            return;
        }
        Student* temp = head;
        while (temp) {
            if (temp->id == ID)
                break;
            temp = temp->next;
        }
        if (temp != NULL) {
            cout << "ID: " << temp->id << ", Name: " << temp->name
                << ", Email: " << temp->email << ", Phone: " << temp->phone
                << ", Address: " << temp->address;
        }
    }

    void deleteStudentById(int id) {
        if (!head) {
            cout << "No students to delete." << endl;
            return;
        }

        // If the head node itself is the student to delete
        if (head->id == id) {
            Student* temp = head;
            head = head->next;
            delete temp;
            cout << "Student deleted successfully." << endl;
            return;
        }

        // Traverse the list to find the student and delete
        Student* temp = head;
        while (temp->next && temp->next->id != id) {
            temp = temp->next;
        }

        if (temp->next) {
            Student* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            cout << "Student deleted successfully." << endl;
        }
        else {
            cout << "Student with ID " << id << " not found." << endl;
        }
    }

    // Function to sort students by ID using Quick Sort
    void quickSortById() {
        head = quickSortByIdRec(head);
        cout << "Students sorted by ID." << endl;
        printStudentList();
    }

private:
    // Helper function to perform Quick Sort recursively
    Student* quickSortByIdRec(Student* head) {
        if (!head || !head->next) return head;

        Student* pivot = head;
        Student* lessHead = nullptr, * equalHead = nullptr, * greaterHead = nullptr;

        // Partition the list into three sublists: less, equal, greater
        Student* temp = head;
        while (temp) {
            Student* nextNode = temp->next; // Save the next node before modifying temp->next
            if (temp->id < pivot->id) {
                appendToList(lessHead, temp);
            }
            else if (temp->id == pivot->id) {
                appendToList(equalHead, temp);
            }
            else {
                appendToList(greaterHead, temp);
            }
            temp = nextNode; // Move to the next node
        }

        // Recursively sort the sublists
        lessHead = quickSortByIdRec(lessHead);
        greaterHead = quickSortByIdRec(greaterHead);

        // Merge all parts together
        return mergeLists(lessHead, equalHead, greaterHead);
    }

    // Helper function to append a node to a list
    void appendToList(Student*& list, Student* node) {
        if (!list) {
            // If the list is empty, make the node the head of the list
            list = node;
            node->next = nullptr;
        }
        else {
            // Traverse to the end of the list and append the node
            Student* temp = list;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = node;
            node->next = nullptr; // Ensure the appended node points to nullptr
        }
    }

    // Helper function to merge three lists (less, equal, greater)
    Student* mergeLists(Student* lessHead, Student* equalHead, Student* greaterHead) {
        // Create a dummy node to simplify merging
        Student dummy(0, "", "", "", "", "");
        Student* tail = &dummy;

        // Helper function to append a list to the tail
        auto append = [&](Student* list) {
            if (list) {
                tail->next = list;
                while (tail->next) {
                    tail = tail->next;
                }
            }
            };

        // Append the less, equal, and greater lists in order
        append(lessHead);
        append(equalHead);
        append(greaterHead);

        // Return the merged list (skip the dummy node)
        return dummy.next;
    }

};
//**************************************stack**********************************
template <class T>

class nodeS {
private:
    T prerequisites;
    nodeS* next;
public:
    nodeS(T p) {
        prerequisites = p;
        next = NULL;
    }

    void set_prerequisites(T p) {
        prerequisites = p;
    }

    T get_prerequisites() {
        return prerequisites;
    }

    void set_next(nodeS* n) {
        next = n;
    }

    nodeS<T>* get_next() {
        return next;
    }

};

template <class T>

class stack {
private:
    nodeS<T>* top;

public:
    stack() { top = NULL; }

    bool isEmpty() {
        return top == nullptr;
    }

    void push(T d) {
        nodeS<T>* n = new nodeS<T>(d);
        if (top == nullptr) {
            top = n;
        }
        else {
            n->set_next(top);
            top = n;
        }
    }

    T pop() {
        if (top == nullptr) {
            return T(); // Return default value if stack is empty
        }
        else {
            nodeS<T>* temp = top;
            top = top->get_next();
            T data = temp->get_prerequisites();
            delete temp;
            return data;
        }
    }
    void validatePrerequisites(int courseID, int studentID, EnrollmentHistory& student, BST t) {
        if (t.search(t.get_root(), courseID) == "") {
            cout << "please enter a valid course Id." << endl;
            return;
        }
        vector<string> missingPrereqs;
        while (!isEmpty()) {
            T prereqID = pop();
            string prereqName = t.search(t.get_root(), prereqID);
            if (prereqName.empty()) {
                cout << "Invalid course ID for prerequisite: " << prereqID << endl;
                continue;
            }
            if (student.findCoures(prereqName)) {
                missingPrereqs.push_back(prereqName);
            }
        }
        if (missingPrereqs.empty()) {
            cout << "All prerequisites are satisfied for course " << courseID << "." << endl;
        }
        else {
            cout << "The student is missing the following prerequisite(s) for course " << courseID << ":" << endl;
            for (const auto& m : missingPrereqs) {
                cout << "- " << m << endl;
            }
        }
    }

};

//****************************************sorting and search ***********************************
// Course class
// Sorting Course Classes and Methods
class Course {
private:
    int courseID;
    string courseName;

public:
    Course() : courseID(0), courseName("") {}
    Course(int id, const string& name) : courseID(id), courseName(name) {}

    int getCourseID() const { return courseID; }
    string getCourseName() const { return courseName; }

    void setCourse(int id, const string& name) {
        courseID = id;
        courseName = name;
    }

    void display() const {
        cout << "Course ID: " << courseID << ", Name: " << courseName << endl;
    }
};
int partitionCoursesByNameAndID(vector<Course>& courses, int low, int high);

// Quick Sort Implementation for Sorting Courses by Name and ID
void quickSortCoursesByNameAndID(vector<Course>& courses, int low, int high) {
    if (low < high) {
        int pivot = partitionCoursesByNameAndID(courses, low, high);
        quickSortCoursesByNameAndID(courses, low, pivot - 1);
        quickSortCoursesByNameAndID(courses, pivot + 1, high);
    }
}

int partitionCoursesByNameAndID(vector<Course>& courses, int low, int high) {
    Course pivot = courses[high];
    int i = (low - 1); // index of smaller element

    for (int j = low; j < high; j++) {
        // Compare first by course name alphabetically, then by course ID
        if (courses[j].getCourseName() < pivot.getCourseName() ||
            (courses[j].getCourseName() == pivot.getCourseName() && courses[j].getCourseID() < pivot.getCourseID())) {
            i++;
            swap(courses[i], courses[j]);
        }
    }
    swap(courses[i + 1], courses[high]);
    return i + 1;
}

// Coursestudentnode class for the singly linked list
class Coursestudentnode {
private:
    Course course;      // Stores the course data
    Coursestudentnode* next;   // Pointer to the next studentnode in the list

public:
    // Constructor
    Coursestudentnode(const Course& c) : course(c), next(nullptr) {}

    // Getter for the course
    Course getCourse() const {
        return course;
    }

    // Setter for the course
    void setCourse(const Course& c) {
        course = c;
    }

    // Getter for the next studentnode
    Coursestudentnode* getNext() const {
        return next;
    }

    // Setter for the next studentnode
    void setNext(Coursestudentnode* n) {
        next = n;
    }
};

//*************************************** 7 **********************************************************
template<class T>
class HashTable {
private:
    list<int>* map;
    int s;
    int hash(int data) {
        return data % s;
    }
public:
    HashTable() {
        s = 100;
        map = new list<int>[s];
    }
    HashTable(int size) {
        if (size <= 0) {
            cout << "Invalid size. Setting to default (100)." << endl;
            s = 100;
        }
        s = size;
        map = new list<int>[s];
    }
    ~HashTable() {
        delete[]map;
    }
    void insert(int key) {
        int bucket = hash(key);

        // Optional: Prevent duplicate entries
        if (find(map[bucket].begin(), map[bucket].end(), key) != map[bucket].end()) {
            cout << "Duplicate key " << key << " not inserted." << endl;
            return;
        }

        map[bucket].push_front(key);
        cout << "Key " << key << " inserted into bucket " << bucket << "." << endl;
    }
    void insertCourses(const list<int>& courseIds) {
        for (auto it = courseIds.begin();it != courseIds.end();it++) {
            insert(*it);
        }
    }
    bool search(int data) {
        int bucket = hash(data);
        auto it = find(map[bucket].begin(), map[bucket].end(), data);
        if (it == map[bucket].end()) {
            return false;
        }
        return true;
    }
    void print() {
        for (int i = 0;i < s;i++) {
            cout << i << ":";
            for (auto it = map[i].begin();it != map[i].end();it++) {
                cout << *it << " ";
            }
            cout << endl;
        }
    }
    int getSize() {
        return s;
    }

};

//***********************************queue *****************************************
#include <iostream>
using namespace std;

class Node {
public:
    SLL students;
    int courseid;
    int id;
    Node* next;
    Node(SLL s, int c, int ID) { students = s;next = NULL;;courseid = c;id = ID; }

};

class Waitlist {
private:
    Node* front;
    Node* rear;

public:
    Waitlist() { front = rear = NULL; }

    void enqueue(int courseId, int id, SLL s) {
        Node* newNode = new Node(s, courseId, id);
        if (!rear) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Student " << id << " added to waitlist.\n";
    }

    void dequeue() {
        if (!front) {
            cout << "Waitlist is empty.\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        if (!front)
            rear = nullptr;

        cout << "Student " << temp->id << " enrolled from waitlist.\n";
        delete temp;
    }

    void displayWaitlist() const {
        if (!front) {
            cout << "Waitlist is empty.\n";
            return;
        }
        Node* temp = front;
        cout << "Waitlist: ";
        while (temp) {
            temp->students.displayStudentInfo(temp->id);
            cout << " waiting to  Enroll in course " << temp->courseid << endl;
            temp = temp->next;
        }
        cout << endl;
    }

    ~Waitlist() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

//********************************** class manger **************************************

// The class provides methods for adding, dropping, sorting, displaying, and searching courses.
class Manager {
private:
    BST courseTree; // Binary Search Tree for managing courses
    vector<Course> coursesList;// Vector to store courses for sorting

    // Helper function to find all courses with a given ID
    void findAllCoursesById(const node* root, int id, vector<Course>& result) const {
        if (root == NULL) return;

        // Traverse the left subtree
        findAllCoursesById(root->get_left(), id, result);

        // Check if the current node matches the ID
        if (root->get_courseId() == id) {
            result.push_back(Course(root->get_courseId(), root->get_CourseName()));
        }

        // Traverse the right subtree
        findAllCoursesById(root->get_right(), id, result);
    }

public:
    BST get_tree() { return courseTree; }
    void addCourse() {
        int id, credits;
        string name, instructor;

        cout << "Enter Course ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Course Name: ";
        getline(cin, name);

        cout << "Enter Course Credits: ";
        cin >> credits;
        cin.ignore();

        cout << "Enter Course Instructor: ";
        getline(cin, instructor);

        courseTree.addCourse(courseTree.get_root(), id, name, credits, instructor);

        // Add the course to the courses list for sorting
        coursesList.push_back(Course(id, name));

        cout << "Course added successfully." << endl;
    }

    void sortCourses() {
        // Sort the courses by name and ID
        quickSortCoursesByNameAndID(coursesList, 0, static_cast<int>(coursesList.size()) - 1);

        cout << "Courses sorted by Name and ID." << endl;
        // Display the sorted courses
        for (const auto& course : coursesList) {
            course.display();
        }
    }

    void dropCourse() {
        int id;
        cout << "Enter Course ID to drop: ";
        cin >> id;

        // Find all courses with the given ID
        vector<Course> matchingCourses;
        findAllCoursesById(courseTree.get_root(), id, matchingCourses);

        if (matchingCourses.empty()) {
            cout << "No courses found with ID " << id << "." << endl;
            return;
        }

        // Print all matching courses
        cout << "Courses with ID " << id << ":" << endl;
        for (const auto& course : matchingCourses) {
            course.display();
        }

        // Delete all courses with the given ID
        for (const auto& course : matchingCourses) {
            courseTree.dropCourse(courseTree.get_root(), id);
        }

        cout << "All courses with ID " << id << " deleted successfully." << endl;
    }

    void displayCourses() const {
        cout << "Courses (Inorder Traversal):" << endl;
        courseTree.inorder(courseTree.get_root());
    }

    // Updated searchCourse method to print all courses with the given ID
    void searchCourse() const {
        int id;
        cout << "Enter Course ID to search: ";
        cin >> id;

        // Find all courses with the given ID
        vector<Course> matchingCourses;
        findAllCoursesById(courseTree.get_root(), id, matchingCourses);

        if (matchingCourses.empty()) {
            cout << "No courses found with ID " << id << "." << endl;
        }
        else {
            cout << "Courses with ID " << id << ":" << endl;
            for (const auto& course : matchingCourses) {
                course.display();
            }
        }
    }
    void searchWithHashing() {
        int id;
        cout << "Enter Course ID to search: ";
        cin >> id;
        HashTable<int>hash(courseTree.get_size());
        hash.insertCourses(courseTree.courseIdList());
        if (!hash.search(id)) {
            cout << "No courses found with ID " << id << "." << endl;
        }
        else {
            cout << "Courses with ID " << id << "is found" << endl;
        }
    }
};



int main() {
    SLL studentList;
    Manager courseManager;
    stack<int>prerequisites;
    Waitlist StudenstWaitlist;
    int choice;

    do {
        cout << "\n--- Student Records Management ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Display All Students\n";
        cout << "4. Add Course to Student History\n";
        cout << "5. View Student Enrollment History\n";
        cout << "6. Add Course to System\n";
        cout << "7. Delete Course from System\n";
        cout << "8. Search Student by ID\n";
        cout << "9. Sort Students by ID\n";
        cout << "10. Search Course by ID\n";
        cout << "11. Sort Courses\n";
        cout << "12. Search using hashing\n";
        cout << "13. Validate course prerequisites\n";
        cout << "14. Add a student to the waitlist\n";
        cout << "15. Enroll the first student on the waitlist\n";
        cout << "16, display students information on the waitlist\n";
        cout << "17. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 17: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore();

        switch (choice) {
        case 1:
            studentList.addStudent();
            break;
        case 2:
        {
            int studentId;
            cout << "Enter Student ID to delete: ";
            cin >> studentId;
            studentList.deleteStudentById(studentId); // Pass studentId
        }
        break;
        case 3:
            studentList.displayStudents();
            break;
        case 4:
        {
            int studentId;
            cout << "Enter Student ID to add course to: ";
            cin >> studentId;
            Student* student = studentList.searchStudentById(studentId);
            if (student) {
                string courseName;
                cout << "Enter Course Name to add: ";
                cin.ignore();
                getline(cin, courseName);
                student->history.addRecord(courseName); // Adding course to student's history
            }
            else {
                cout << "Student not found." << endl;
            }
        }
        break;
        case 5:
        {
            int studentId;
            cout << "Enter Student ID to view history: ";
            cin >> studentId;
            Student* student = studentList.searchStudentById(studentId);
            if (student) {
                student->history.viewHistory(); // Viewing student's enrollment history
            }
            else {
                cout << "Student not found." << endl;
            }
        }
        break;
        case 6:
            courseManager.addCourse();
            break;
        case 7:
            courseManager.dropCourse();
            break;
        case 8:
        {
            int studentId;
            cout << "Enter Student ID to search: ";
            cin >> studentId;
            Student* student = studentList.searchStudentById(studentId);
            if (student) {
                cout << "Student found: ID: " << student->id << ", Name: " << student->name << endl;
            }
            else {
                cout << "Student not found." << endl;
            }
        }
        break;
        case 9:
            studentList.quickSortById();
            break;

        case 10:
            courseManager.searchCourse();
            break;

        case 11:
            courseManager.sortCourses();
            break;
        case 12:
            courseManager.searchWithHashing();
            break;
        case 13: {
            int num;
            cout << "enter the number of prerequisites" << endl;
            cin >> num;
            cout << "enter the id of each prerequisite course" << endl;
            while (num--) {
                int temp;
                cin >> temp;
                prerequisites.push(temp);
            }
            int courseId;
            int studentId;
            cout << "enter the Coures and student ID:" << endl;
            cin >> courseId >> studentId;
            prerequisites.validatePrerequisites(courseId, studentId, studentList.searchStudentById(studentId)->history, courseManager.get_tree());
            break;
        }
        case 14: {
            int id;
            int courseID;
            cout << "Course ID to enroll in:" << endl;
            cin >> courseID;
            cout << "Student ID to enroll:" << endl;
            cin >> id;
            StudenstWaitlist.enqueue(courseID, id, studentList);
            break;
        }
        case 15: {
            StudenstWaitlist.dequeue();
            break;
        }
        case 16: {
            StudenstWaitlist.displayWaitlist();
            break;
        }
        case 17:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please select a valid option." << endl;
        }
    } while (choice != 17);

    return 0;
}
