#include <algorithm>
#include <cctype>
#include <climits>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <windows.h>
#include <iomanip>

using namespace std;

const HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

// declaring functions
void initiate_student();
void initiate_librarian();
void initiate_registrar();
void initiate_department_head();
void initiate_students_affair();
void initiate_sports_and_clubs();
void initiate_college_admin();
void initiate_dining();
void initiate_dormitory();
void main_menu();
void write_to_file();
// student

bool input_check(string input)
{
  for (char i : input)
  {
    if (!isdigit(i))
    {
      return false;
    }
  }
  return true;
}
struct Eligablity
{
  vector<string> issues;
  bool eligable;
};
struct Student
{
  char type;
  string id;
  string name;
  bool library;
  bool department_head;
  bool students_affair;
  bool sports_and_clubs;
  bool college_admin;
  bool dining;
  bool dormitory;
  void menu();
  bool registrar;
  Eligablity isEligable();
  bool *values[8] = {&this->library, &this->department_head,
                     &this->students_affair, &this->sports_and_clubs,
                     &this->college_admin, &this->dining,
                     &this->dormitory};
  unordered_map<int, string> map;
  void mapIt();
};

static vector<Student *> Student_table;
void Student::mapIt()
{
  map[0] = "library";
  map[1] = "department_head";
  map[2] = "students_affair";
  map[3] = "sports_and_clubs";
  map[4] = "college_admin";
  map[5] = "Dining office";
  map[6] = "Dormitory";
}

Eligablity Student::isEligable()
{
  Eligablity res;
  this->mapIt();
  for (int i = 0; i < 7; i++)
  {
    if (*values[i] == 0)
    {
      // cout << i << *values[i];
      res.eligable = false;
      res.issues.push_back(map[i]);
      // cout << map[i] << endl;
    }
  }
  return res;
}

bool search(string target, Student *stud)
{
  vector<Student> possible_list = {};
  for (Student *i : Student_table)
  {
    if (i->name.find(target) != string::npos ||
        i->id.find(target) != string::npos)
    {
      Student cur = *i;
      possible_list.push_back(cur);
    }
  }
  if (possible_list.size() == 0)
  {
    cout << "No students by this name/ id exist." << endl;
    return false;
  }
  int numbers = 1;
  for (Student i : possible_list)
  {
    cout << numbers << i.name << ", " << i.id << endl;
    numbers++;
  }

  cout << "\nIf you see your name in the list choose the corresponding number if "
          "not choose 0: ";
  string choice;
  getline(cin, choice);
  std::cout << "\033[2J\033[1;1H";
  if (!input_check(choice))
  {
    cout << "\nYour choice is invalid. You will be directed back to the main "
            "menu. "
         << endl;
    main_menu();
  }
  else if (stoi(choice) == 0)
  {
    cout << "\nThe name or Id entered does not correspond to any registered "
            "student."
         << endl;
    return false;
  }
  else if (stoi(choice) > numbers)
  {
    cout << "\nYour choice is invalid. You will be directed back to the main "
            "menu. "
         << endl;
    main_menu();
  }
  // cout << stud << endl;
  *stud = possible_list[stoi(choice) - 1];
  // cout << stud << endl;
  possible_list.clear();
  return true;
};

string btos(bool x)
{
  if (x == true)
  {
    return "true";
  }
  else
  {
    return "false";
  }
}

void student_table_loop()
{

  cout << "Name" << setw(10) << "ID"
       << "\t\t"
       << "library"
       << "\t\t"
       << "department_head"
       << "\t\t"
       << "students_affair"
       << "\t\t"
       << "sports_and_clubs"
       << "\t"
       << "college_admin"
       << "\t"
       << "dining"
       << "\t\t"
       << "dormitory" << endl;
  for (Student *i : Student_table)
  {
    int len = 15 - int(i->name.size());
    cout << i->name << setw(len);
    // for (int i = 0; i < len; i++) {
    // cout << '\t';
    // }
    cout << i->id << "\t\t" << btos(i->library) << "\t\t" << btos(i->department_head) << "\t\t\t" << btos(i->students_affair) << "\t\t\t" << btos(i->sports_and_clubs) << "\t\t\t" << btos(i->college_admin) << setw(16) << btos(i->dining) << "\t\t" << btos(i->dormitory) << endl;
  }
}
// menu for students
// menu for students
void Student::menu()
{
  cout << "To request clearance enter '1':  ";
  string choice;
  getline(cin, choice);
  std::cout << "\033[2J\033[1;1H";

  if (!input_check(choice))
  {
    cout << "\nYour choice is invalid. You will be directed back to the main "
            "menu. "
         << endl;
    main_menu();
  }

  else if (stoi(choice) == 1)
  {
    cout << " Enter your ID/Name  : ";
    string query;
    getline(cin, query);
    std::cout << "\033[2J\033[1;1H";
    if (search(query, this))
    {
      Eligablity issue = this->isEligable();
      if (issue.eligable)
      {
        cout << "Clearance granted!!" << endl;
      }
      else
      {
        cout << "Clearance not granted. You have issues raised by the "
                "following offices:"
             << endl;
        for (int i = 0; i < issue.issues.size(); i++)
        {
          cout << i + 1 << ". " << issue.issues[i] << endl;
        }
        cout << "________________________________________________________";
      }
    }
  }
  else
  {
    cout << "Invalid input!";
  }
}
void initiate_student()
{
  Student *stud = new Student;
  stud->menu();
}
// Function for librarian
string password_lib = "lib123";
void initiate_librarian()
{
  string pass;
  cout << " Enter passowrd: ";
  getline(cin, pass);
  std::cout << "\033[2J\033[1;1H";
  if (pass != password_lib)
  {
    string c;
  here:
    cout << "Incorrect password! Do you want to try again y/n?: ";
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      initiate_librarian();
      return;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto here;
    }
  }
  cout << "Passowrd correct! " << endl;
srch:
  cout << "Search the name/id of a student: ";
  string query;
  Student found;
  getline(cin, query);
  std::cout << "\033[2J\033[1;1H";
  if (!search(query, &found))
  {
  choose_again:
    cout << "to enter another name choose 'y' to exit choose 'n' : ";
    string choi;
    getline(cin, choi);
    if (choi == "y")
    {
      goto srch;
    }
    else if (choi == "n")
    {
      return;
    }
    else
    {
      cout << "Invalid choice" << endl;
      goto choose_again;
    }
  }

  if (found.library)
  {
  there:
    cout << " Do you want to raise an issue y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->library = false;
          break;
        }
      }

      return;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto there;
    }
  }
  else
  {
  second_there:
    cout << "Is the issue resolved y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->library = true;
          break;
        }
      }

      return;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto second_there;
    }
  }
}

// Function for department_head
string password_department = "dep123";
void initiate_department_head()
{
  string pass;
  cout << " Enter passowrd: ";
  getline(cin, pass);
  if (pass != password_department)
  {
    string c;
  here:
    cout << "Incorrect password! Do you want to try again y/n?: ";
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      initiate_department_head();
      return;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto here;
    }
  }
  cout << "Passowrd correct! " << endl;
srch:
  cout << "Search the name/id of a student: ";
  string query;
  Student found;
  getline(cin, query);
  if (!search(query, &found))
  {
  choose_again:
    cout << "to enter another name choose 'y' to exit choose 'n' : ";
    string choi;
    getline(cin, choi);
    std::cout << "\033[2J\033[1;1H";
    if (choi == "y")
    {
      goto srch;
    }
    else if (choi == "n")
    {
      return;
    }
    else
    {
      cout << "Invalid choice" << endl;
      goto choose_again;
    }
  }

  if (found.department_head)
  {
  there:
    cout << " Do you want to raise an issue y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->department_head = false;
          break;
        }
      }

      return;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto there;
    }
  }
  else
  {
  second_there:
    cout << "Is the issue resolved y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->department_head = true;
          break;
        }
      }
      cout << "The issue has been removed from record" << endl;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto second_there;
    }
  }
}

// Function for Dormitory
string password_dorm = "dorm123";
void initiate_dormitory()
{
  string pass;
  cout << " Enter passowrd: ";
  getline(cin, pass);
  std::cout << "\033[2J\033[1;1H";
  if (pass != password_dorm)
  {
    string c;
  here:
    cout << "Incorrect password! Do you want to try again y/n?: ";
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    ;
    if (c == "y")
    {
      initiate_dormitory();
      return;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto here;
    }
  }
  cout << "Passowrd correct! " << endl;
srch:
  cout << "Search the name/id of a student: ";
  string query;
  Student found;
  getline(cin, query);
  std::cout << "\033[2J\033[1;1H";
  if (!search(query, &found))
  {
  choose_again:
    cout << "to enter another name choose 'y' to exit choose 'n' : ";
    string choi;
    getline(cin, choi);
    if (choi == "y")
    {
      goto srch;
    }
    else if (choi == "n")
    {
      return;
    }
    else
    {
      cout << "Invalid choice" << endl;
      goto choose_again;
    }
  }

  if (found.dormitory)
  {
  there:
    cout << " Do you want to raise an issue y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->dormitory = false;
          break;
        }
      }
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto there;
    }
  }
  else
  {
  second_there:
    cout << "Is the issue resolved y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->dormitory = true;
          break;
        }
      }
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto second_there;
    }
  }
}

// Function for college_admin
string password_coll = "coll123";
void initiate_college_admin()
{
  string pass;
  cout << " Enter passowrd: ";
  getline(cin, pass);
  std::cout << "\033[2J\033[1;1H";
  if (pass != password_coll)
  {
    string c;
  here:
    cout << "Incorrect password! Do you want to try again y/n?: ";
    getline(cin, c);
    if (c == "y")
    {
      initiate_college_admin();
      return;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto here;
    }
  }
  cout << "Passowrd correct! " << endl;
srch:
  cout << "Search the name/id of a student: ";
  string query;
  Student found;
  getline(cin, query);
  std::cout << "\033[2J\033[1;1H";
  if (!search(query, &found))
  {
  choose_again:
    cout << "to enter another name choose 'y' to exit choose 'n' : ";
    string choi;
    getline(cin, choi);
    std::cout << "\033[2J\033[1;1H";
    if (choi == "y")
    {
      goto srch;
    }
    else if (choi == "n")
    {
      return;
    }
    else
    {
      cout << "Invalid choice" << endl;
      goto choose_again;
    }
  }

  if (found.college_admin)
  {
  there:
    cout << " Do you want to raise an issue y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->college_admin = false;
          break;
        }
      }
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto there;
    }
  }
  else
  {
  second_there:
    cout << "Is the issue resolved y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->college_admin = true;
          break;
        }
      }
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto second_there;
    }
  }
}

// Function for sports_and_clubs
string password_spacl = "spacl123";
void initiate_sports_and_clubs()
{
  string pass;
  cout << " Enter passowrd: ";
  getline(cin, pass);
  std::cout << "\033[2J\033[1;1H";
  if (pass != password_spacl)
  {
    string c;
  here:
    cout << "Incorrect password! Do you want to try again y/n?: ";
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      initiate_sports_and_clubs();
      return;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto here;
    }
  }
  cout << "Passowrd correct! " << endl;
srch:
  cout << "Search the name/id of a student: ";
  string query;
  Student found;
  getline(cin, query);
  std::cout << "\033[2J\033[1;1H";
  if (!search(query, &found))
  {
  choose_again:
    cout << "to enter another name choose 'y' to exit choose 'n' : ";
    string choi;
    getline(cin, choi);
    std::cout << "\033[2J\033[1;1H";
    if (choi == "y")
    {
      goto srch;
    }
    else if (choi == "n")
    {
      return;
    }
    else
    {
      cout << "Invalid choice" << endl;
      goto choose_again;
    }
  }

  if (found.sports_and_clubs)
  {
  there:
    cout << " Do you want to raise an issue y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->sports_and_clubs = false;
          break;
        }
      }
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto there;
    }
  }
  else
  {
  second_there:
    cout << "Is the issue resolved y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->sports_and_clubs = true;
          break;
        }
      }
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto second_there;
    }
  }
}

// Function for students_affair
string password_studaff = "staf123";
void initiate_students_affair()
{
  string pass;
  cout << " Enter passowrd: ";
  getline(cin, pass);
  std::cout << "\033[2J\033[1;1H";
  if (pass != password_studaff)
  {
    string c;
  here:
    cout << "Incorrect password! Do you want to try again y/n?: ";
    getline(cin, c);
    if (c == "y")
    {
      initiate_students_affair();
      return;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto here;
    }
  }
  cout << "Passowrd correct! " << endl;
srch:
  cout << "Search the name/id of a student: ";
  string query;
  Student found;
  getline(cin, query);
  std::cout << "\033[2J\033[1;1H";
  if (!search(query, &found))
  {
  choose_again:
    cout << "to enter another name choose 'y' to exit choose 'n' : ";
    string choi;
    getline(cin, choi);
    std::cout << "\033[2J\033[1;1H";
    if (choi == "y")
    {
      goto srch;
    }
    else if (choi == "n")
    {
      return;
    }
    else
    {
      cout << "Invalid choice" << endl;
      goto choose_again;
    }
  }

  if (found.students_affair)
  {
  there:
    cout << " Do you want to raise an issue y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->students_affair = false;
          break;
        }
      }
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto there;
    }
  }
  else
  {
  second_there:
    cout << "Is the issue resolved y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->students_affair = true;
          break;
        }
      }
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto second_there;
    }
  }
}

// Function for dining
string password_dining = "din123";
void initiate_dining()
{
  string pass;
  cout << " Enter passowrd: ";
  getline(cin, pass);
  std::cout << "\033[2J\033[1;1H";
  if (pass != password_dining)
  {
    string c;
  here:
    cout << "Incorrect password! Do you want to try again y/n?: ";
    getline(cin, c);
    if (c == "y")
    {
      initiate_dining();
      return;
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto here;
    }
  }
  cout << "Passowrd correct! " << endl;
srch:
  cout << "Search the name/id of a student: ";
  string query;
  Student found;
  getline(cin, query);
  std::cout << "\033[2J\033[1;1H";
  if (!search(query, &found))
  {
  choose_again:
    cout << "to enter another name choose 'y' to exit choose 'n' : ";
    string choi;
    getline(cin, choi);
    std::cout << "\033[2J\033[1;1H";
    if (choi == "y")
    {
      goto srch;
    }
    else if (choi == "n")
    {
      return;
    }
    else
    {
      cout << "Invalid choice" << endl;
      goto choose_again;
    }
  }

  if (found.dining)
  {
  there:
    cout << " Do you want to raise an issue y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->dining = false;
          break;
        }
      }
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto there;
    }
  }
  else
  {
  second_there:
    cout << "Is the issue resolved y/n?: ";

    string c;
    getline(cin, c);
    std::cout << "\033[2J\033[1;1H";
    if (c == "y")
    {
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          student->dining = true;
          break;
        }
      }
    }
    else if (c == "n")
    {
      return;
    }
    else
    {
      cout << "Your input is not valid try again.";
      goto second_there;
    }
  }
}
// registrar menu
string password_registrar = "reg123";
void registrar_menu()
{
    string pass;
    cout << " Enter passowrd: ";
    getline(cin, pass);
    std::cout << "\033[2J\033[1;1H";
    if (pass != password_registrar)
    {
        string c;
    here:
        cout << "Incorrect password! Do you want to try again y/n?: ";
        getline(cin, c);
        if (c == "y")
        {
            registrar_menu();
            return;
        }
        else if (c == "n")
        {
            return;
        }
        else
        {
            cout << "Your input is not valid try again.";
            goto here;
        }
    }
main_reg:
  cout << "1. View Clearance record of all students" << endl;
  cout << "2. Update Students name/ id" << endl;
  cout << "3. Delete Student record." << endl;

  cout << "Enter a valid choice:  ";
  string choice;
again:
  getline(cin, choice);
  std::cout << "\033[2J\033[1;1H";
  if (!(input_check(choice)))
  {
    cout << "Your choice is not valid! Choose again:  ";
    goto again;
  }
  else if (stoi(choice) > 3)
  {
    cout << "Your choice is not valid! Choose again:  ";
    goto again;
  }
  string choice1;
  string choice2;
  string query4;
  Student found4;
  string identify;
  switch (stoi(choice))
  {
  case 1:
    student_table_loop();
    break;
  case 2:
    cout << "To edit name enter 1, to edit ID enter 2.";
    cout << "Enter a valid choice:  ";

  again1:
    getline(cin, choice1);
    std::cout << "\033[2J\033[1;1H";
    if (!(input_check(choice1)))
    {
      cout << "Your choice is not valid! Choose again:  ";
      goto again1;
    }
    else if (stoi(choice1) > 2)
    {
      cout << "Your choice is not valid! Choose again:  ";
      goto again1;
    }
    else if (stoi(choice1) == 1)
    {
    srch:
      cout << "Search the name/id of the student you want to edit: ";
      string query;
      Student found;
      getline(cin, query);
      std::cout << "\033[2J\033[1;1H";
      if (!search(query, &found))
      {
      choose_again:
        cout << "to enter another name choose 'y' to exit choose 'n' : ";
        string choi;
        getline(cin, choi);
        if (choi == "y")
        {
          goto srch;
        }
        else if (choi == "n")
        {
          return;
        }
        else
        {
          cout << "Invalid choice" << endl;
          goto choose_again;
        }
      }
      for (Student *student : Student_table)
      {
        if (student->id == found.id)
        {
          cout << "Enter the name you want to replace it with: ";
          string name;
          cin >> name;
          student->name = name;
          break;
        }
      }
    }
    else if (stoi(choice1) == 2)
    {

    srch2:
      cout << "Search the name/id of the student you want to edit: ";
      string query2;
      Student found2;
      getline(cin, query2);
      std::cout << "\033[2J\033[1;1H";
      if (!search(query2, &found2))
      {
      choose_again2:
        cout << "to enter another name choose 'y' to exit choose 'n' : ";
        string choi2;
        getline(cin, choi2);
        if (choi2 == "y")
        {
          goto srch2;
        }
        else if (choi2 == "n")
        {
          return;
        }
        else
        {
          cout << "Invalid choice" << endl;
          goto choose_again2;
        }
      }
      for (Student *student : Student_table)
      {
        if (student->id == found2.id)
        {
          cout << "Enter the id you want to replace it with: ";
          string id;
          cin >> id;
          student->id = id;
          break;
        }
      }
    }
    else if (stoi(choice1) == 3)
    {
    srch3:
      cout << "Search the name/id of the student you want to edit: ";
      string query3;
      Student found3;
      getline(cin, query3);
      std::cout << "\033[2J\033[1;1H";
      if (!search(query3, &found3))
      {
      choose_again3:
        cout << "to enter another name choose 'y' to exit choose 'n' : ";
        string choi3;
        getline(cin, choi3);
        if (choi3 == "y")
        {
          goto srch3;
        }
        else if (choi3 == "n")
        {
          return;
        }
        else
        {
          cout << "Invalid choice" << endl;
          goto choose_again3;
        }
      }
      for (Student *student : Student_table)
      {
        if (student->id == found3.id)
        {
          cout << "Enter the name you want to replace it with: ";
          string name;
          cin >> name;
          student->name = name;

          cout << "Enter the id you want to replace it with: ";
          string id;
          cin >> id;
          student->id = id;
          break;
        }
      }
    }
    break;
  case 3:
  srchh:
    cout << "Search the name/id of the student you want to delete: ";
    getline(cin, query4);
    std::cout << "\033[2J\033[1;1H";
    if (!search(query4, &found4))
    {
    choose_againn:
      cout << "to enter another name choose 'y' to exit choose 'n' : ";
      string choi4;
      getline(cin, choi4);
      if (choi4 == "y")
      {
        goto srchh;
      }
      else if (choi4 == "n")
      {
        return;
      }
      else
      {
        cout << "Invalid choice" << endl;
        goto choose_againn;
      }
    }
    for (Student *student : Student_table)
    {
      if (student->id == found4.id)
      {
        identify = student->id;
        break;
      }
    }
    for (auto i = 0; i < Student_table.size(); i++)
    {
      if (Student_table[i]->id == identify)
      {
        Student_table.erase(Student_table.begin() + i);
      }
    }

    break;
  default:
    cout << "Your choice is invalid!" << endl;
    goto main_reg;
  }
}
// Registrar
void initiate_registrar()
{
  registrar_menu();
}
// main menu
void main_menu()
{
main:
  SetConsoleTextAttribute(console, 46); // cout << "Program Initiated"; std::cout << "\033[2J\033[1;1H";
  cout << " ___________________________________" << endl;
  cout << "|                                   |" << endl;
  cout << "|     Clearance Managment System    |" << endl;
  cout << "|___________________________________|" << endl;
  cout << "|                                   |" << endl;
  cout << "|Sign in as:                        |" << endl;
  cout << "| 1. A Student                      |" << endl;
  cout << "| 2. A Librarian                    |" << endl;
  cout << "| 3. A Registrar                    |" << endl;
  cout << "| 4. A department_head              |" << endl;
  cout << "| 5. A students_affair staff        |" << endl;
  cout << "| 6. A sports_and_clubs staff       |" << endl;
  cout << "| 7. A college_admin                |" << endl;
  cout << "| 8. A dining office staff          |" << endl;
  cout << "| 9. A dormitory proctor            |" << endl;
  cout << "| 10. To exit program               |" << endl;
  cout << "|___________________________________|" << endl;
  string choice;

  cout << "Enter a valid choice:  ";
again:
  getline(cin, choice);
  std::cout << "\033[2J\033[1;1H";
  if (!(input_check(choice)))
  {
    cout << "Your choice is not valid! Choose again:  ";
    goto again;
  }
  else if (stoi(choice) > 10)
  {
    cout << "Your choice is not valid! Choose again:  ";
    goto again;
  }
  SetConsoleTextAttribute(console, 37);
  switch (stoi(choice))
  {
  case 1:
    initiate_student();
    break;
  case 2:
    initiate_librarian();
    break;
  case 3:
    initiate_registrar();
    break;
  case 4:
    initiate_department_head();
    break;
  case 5:
    initiate_students_affair();
    break;
  case 6:
    initiate_sports_and_clubs();
    break;
  case 7:
    initiate_college_admin();
    break;
  case 8:
    initiate_dining();
    break;
  case 9:
    initiate_dormitory();
    break;
  case 10:
    cout << "You have chose to exit the program!" << endl;
    write_to_file();
    exit(0);
  default:
    // write_to_file();
    cout << "Your choice is invalid!" << endl;
    goto main;
  }
  // for (const auto x : Student_table) {
  // cout << x.name << " ->" << x.college_admin;
  //}
}
bool stob(string x)
{
  if (x[0] == 't')
  {
    return true;
  }
  return false;
}
void write_to_file()
{
  //cout << "write to ";
  fstream outputFile;
  outputFile.open("student_record.csv", ios::out);

  if (!outputFile.is_open())
  {
    cout << "Error: Could not open the file 'student_record' for writing." << endl;
    return;
  }

  //cout << "File is succesfully opened.";
  for (const auto &student : Student_table)
  {
    // cout << student->name << "  " << student->library;
    outputFile << student->id << ","
               << student->name << ","
               << (student->library ? "true" : "false") << ","
               << (student->department_head ? "true" : "false") << ","
               << (student->students_affair ? "true" : "false") << ","
               << (student->sports_and_clubs ? "true" : "false") << ","
               << (student->college_admin ? "true" : "false") << ","
               << (student->dining ? "true" : "false") << ","
               << (student->dormitory ? "true" : "false") << "\n";
  }

  outputFile.close();
}

void parsed_file()
{
  fstream myFile;
  myFile.open("student_record.csv");
  string line = "";
  if (!myFile.is_open())
  {
    cout << "File has not opened.";
    return;
  }
  while (getline(myFile, line))
  {

    Student *temp = new Student;
    string tmp;
    stringstream myString(line);
    getline(myString, temp->id, ',');
    getline(myString, temp->name, ',');
    getline(myString, tmp, ',');
    temp->library = stob(tmp);
    // getline(myString, tmp, ',');
    // temp->registrar = stob(tmp);
    getline(myString, tmp, ',');
    temp->department_head = stob(tmp);
    getline(myString, tmp, ',');
    temp->students_affair = stob(tmp);
    getline(myString, tmp, ',');
    temp->sports_and_clubs = stob(tmp);
    getline(myString, tmp, ',');
    temp->college_admin = stob(tmp);
    getline(myString, tmp, ',');
    temp->dining = stob(tmp);
    getline(myString, tmp, ',');
    temp->dormitory = stob(tmp);
    Student_table.push_back(temp);
  }
}
int main()
{
  parsed_file();
repeat:
  main_menu();
  string action;
wrong_choice:
  cout << " \nTo exit the program enter 'e' to continue enter 'y':   ";
  getline(cin, action);
  if (action == "y" || action == "Y")
  {
    goto repeat;
  }
  else if (action == "e" || action == "E")
  {
    write_to_file();
    cout << " You have exited the program" << endl;
    return 0;
  }
  else
  {
    cout << "Your choice is invalid choose again. " << endl;
    goto wrong_choice;
  }
  write_to_file();
}
