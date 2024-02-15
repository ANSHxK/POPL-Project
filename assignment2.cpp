#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

class Employee
{
    public:
        int pay;
        string name;
        string id;
    
   
    Employee(string name, string id, int pay)
    {
        this->name = name;
        this->id = id;
        this->pay = pay;
    }
    // default constructor
    Employee()
    {   
        this->name = "";
        this->id = "";
        this->pay = 0;
    }
    static std::vector<Employee> getData(string file)
    {
        ifstream infile;
        infile.open(file.c_str());
        if (!infile)
        {
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        string line;
        // resset the file pointer
        infile.clear();
        infile.seekg(0, ios::beg);
        
        // create a vector of employees
        vector<Employee> employees;

        string arr[3];
        int count = 0;
        while (getline(infile, line))
        {
            if (count == 0)
            {
                count++;
                continue;
            }
            // each element of array is tab delimited in the line
            for (int i = 0; i < 3; i++)
            {
                // find the position of the tab
                int pos = line.find("\t");
                // extract the string from the beginning to the tab
                arr[i] = line.substr(0, pos);
                // remove the string from the beginning to the tab
                line.erase(0, pos + 1);
            }
            // create an employee
            int pay = stoi(arr[2]);
            Employee employee(arr[1], arr[0], pay);
            
            // add employee to the vector
            employees.push_back(employee);
            count ++;
        }
        infile.close();

        return employees;
    }

    static void putData(vector<Employee> employees, string file)
    {
        ofstream outfile;
        outfile.open(file.c_str());
        if (!outfile)
        {
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        outfile.seekp(0, ios::end);
        outfile << "Employees" << endl;
        outfile << "Number of employees: " << employees.size() << endl;

        outfile << "Name" << "\t" << "ID" << "\t" << "Pay" << endl;
        for (const auto& employee : employees)
        {
            outfile << employee.name << "\t" << employee.id << "\t" << employee.pay << endl;
        }
        outfile << "-----------------------------------" << endl;
        outfile.close();
    }

};

// instructor class, inherits from employee
class Instructor: public Employee
{
    public:
        string course;
    
    // constructor to set the name, age, pay and course
    Instructor(string name, string id, int pay, string course):Employee(name, id, pay)
    {
        this->course = course;
    }
    // default constructor
    Instructor()
    {
        this->name = "";
        this->id = "";
        this->pay = 0;
        this->course = "";
    }
    static vector<Instructor> getData(vector <Employee> employees, string file)
    {
        ifstream infile;
        infile.open(file.c_str());
        if (!infile)
        {
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        string line;
        // resset the file pointer
        infile.clear();
        infile.seekg(0, ios::beg);
        // create a vector of instructors
        vector<Instructor> instructors;
        string arr[2];
        int count = 0;
        while (getline(infile, line))
        {
            if (count == 0)
            {
                count++;
                continue;
            }
            for (int i = 0; i < 2; i++)
            {
                // find the position of the tab
                int pos = line.find("\t");
                // extract the string from the beginning to the tab
                arr[i] = line.substr(0, pos);
                // remove the string from the beginning to the tab
                line.erase(0, pos + 1);
            }
            // create an instructor
            Instructor instructor(getInstructorName(employees, arr[0]), arr[0], getInstructorPay(employees, arr[0]), arr[1]);
            // add the instructor to the vector
            instructors.push_back(instructor);
            count ++;
        }
        infile.close();

        return instructors;

    }

    // helper function to get the instructor's name from array of employees
    static string getInstructorName(vector<Employee> employees, string id)
    {
        for (const auto& employee : employees)
        {
            if (employee.id == id)
            {
                return employee.name;
            }
        }
        return "";
    }
    // helper function to get the instructor's pay from array of employees
    static int getInstructorPay(vector<Employee> employees, string id)
    {
        for(const auto& employee : employees)
        {
            if(employee.id == id)
            {
                return employee.pay;
            }
        }
        return 0;
    }

};

// student class
class Student
{
    public:
        string id;
        string name;
        int fees_paid;
        string c1;
        string c2;
        string c3;
    
    // constructor to set the name, age, pay, course and fees
    Student(string name, string id, int fees_paid, string c1, string c2, string c3)
    {
        this->name = name;
        this->id = id;
        this->fees_paid = fees_paid;
        this->c1 = c1;
        this->c2 = c2;
        this->c3 = c3;
    }

    // default constructor
    Student()
    {
        this->name = "";
        this->id = "";
        this->fees_paid = 0;
        this->c1 = "";
        this->c2 = "";
        this->c3 = "";
    }

    // returns an array of students
    static vector<Student> getData(string file)
    {
        ifstream infile;
        infile.open(file.c_str());
        if (!infile)
        {
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        string line;
        // create a vector of students
        vector<Student> students;
        // resset the file pointer
        infile.clear();
        infile.seekg(0, ios::beg);
        string arr[6];
        int count = 0;
        while (getline(infile, line))
        {
            if (count == 0)
            {
                count++;
                continue;
            }
            // each element of array is tab delimited in the line
            for (int i = 0; i < 6; i++)
            {
                // find the position of the tab
                int pos = line.find("\t");
                // extract the string from the beginning to the tab
                arr[i] = line.substr(0, pos);
                // remove the string from the beginning to the tab
                line.erase(0, pos + 1);
            }
            // create a student
            int fees_paid = stoi(arr[2]);
            Student student(arr[1], arr[0], fees_paid, arr[3], arr[4], arr[5]);
            // add the student to the vector
            students.push_back(student);
            count ++;
        }
        infile.close();

        return students;
    }


    static void putTAData(vector<Student>students, vector<Instructor> instructors, string file)
    {
        ofstream outfile;
        outfile.open(file.c_str(), std::ios_base::app);
        if (!outfile)
        {
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        outfile.seekp(0, ios::end);
        outfile << "Students who are instructors" << endl;

        outfile << "Name" << "\t" << "ID" << "\t" << "Fees Paid" << "\t" << " C1 " << "\t" << "C2" << "\t" << "C3" << endl;
        for(const auto& student : students)
        {
            if(isInstructor(instructors, student.id))
            {
                outfile << student.name << "\t" << student.id << "\t" << student.fees_paid << "\t" << student.c1 << "\t" << student.c2 << "\t" << student.c3 << endl;
            }
        }
        outfile << "-----------------------------------" << endl;
        outfile.close();
    }

    static void putData(vector<Student> students, string file)
    {
        ofstream outfile;
        outfile.open(file.c_str(), std::ios_base::app);
        if (!outfile)
        {
            cout << "Unable to open file";
            exit(1); // terminate with error
        }
        outfile.seekp(0, ios::end);
        outfile << "Students" << endl;
        outfile << "Number of students: " << students.size() << endl;

        outfile << "Name" << "\t" << "ID" << "\t" << "Fees Paid" << "\t" << " C1 " << "\t" << "C2" << "\t" << "C3" << endl;
        for (const auto& student : students)
        {
            outfile << student.name << "\t" << student.id << "\t" << student.fees_paid << "\t" << student.c1 << "\t" << student.c2 << "\t" << student.c3 << endl;
        }
        outfile << "-----------------------------------" << endl;
        outfile.close();
    }

    // write list of students who are teaching assistants
    

    static bool isInstructor(vector<Instructor> instructors, string id)
    {
        for(const auto& instructor : instructors)
        {
            if(instructor.id == id)
            {
                return true;
            }
        }
        return false;
    }

    // write list of students whoa re not teaching assistants
    static void putNonTAData(vector<Student>students, vector<Instructor> instructors, string file)
    {
        ofstream outfile;
        outfile.open(file.c_str(), std::ios_base::app);
        if (!outfile)
        {
            cout << "Unable to open file";
            exit(1); // terminate with error
        }

        outfile.seekp(0, ios::end);
        outfile << "Students who are not instructors" << endl;

        outfile << "Name" << "\t" << "ID" << "\t" << "Fees Paid" << "\t" << " C1 " << "\t" << "C2" << "\t" << "C3" << endl;
        for(const auto& student : students)
        {
            if(!isInstructor(instructors, student.id))
            {
                outfile << student.name << "\t" << student.id << "\t" << student.fees_paid << "\t" << student.c1 << "\t" << student.c2 << "\t" << student.c3 << endl;
            }
        }
        outfile << "-----------------------------------" << endl;
        outfile.close();
    }

    // helper function to check if a student is also an instructor
    
};

int main(int argc, char* argv[])
{
    if(argc < 4 || argc > 5)
    {
        cout << "Please enter the correct number of arguments" << endl;
        cout << "Usage: ./assignment2 <employee.txt> <instructor.txt> <student.txt> <output.txt>" << endl;
        return 0;
    }
    string employee_file (argv[1]);
    string instructor_file (argv[2]);
    string student_file (argv[3]);
    string output_file (argv[4]);

    // call the getData() method of each class, passing the data to the next class and to putData() method
    vector<Employee> employees = Employee::getData(employee_file);
    Employee::putData(employees, output_file);
    vector<Instructor> instructors = Instructor::getData(employees, instructor_file);

    vector<Student> students = Student::getData(student_file);
    Student::putData(students, output_file);
    Student::putTAData(students, instructors, output_file);
    Student::putNonTAData(students, instructors, output_file);

}