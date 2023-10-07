#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<list>
#include<iterator>
#include <fstream>
using namespace std;



class Student {

	string st_name;
	vector<int>Grades;
public:
	static int count;

	Student() : st_name("Unknown") {}
	Student(const string& arg_st_name) : st_name(arg_st_name) {}
	Student(const string& arg_st_name,const vector<int>& arg_Grades) : st_name(arg_st_name) { Grades=arg_Grades;}
	void setst_name(const string& arg_st_name) { st_name=arg_st_name;}
	void setGrades(const vector<int>& arg_Grades) { Grades=arg_Grades;}
	string getst_name() const { return st_name;}
	vector<int> getGrades() const { return Grades;}
	void Add_Grades(int k) { cout<<"\nAdd a  grade: "; cin>>k; Grades.push_back(k); }


 double Average_Grades() {
	 double result=0.00;
	 int sum=0;
 for (int i=0;i<Grades.size();i++) sum+=Grades.at(i);

	  if (Grades.size()!=0) result=sum/Grades.size();
	  
 return result;
 }

 int Sum_of_Grades(int k) { 
	 k=0;
	 for (int i=0;i<Grades.size();i++) 
		 k+=Grades.at(i);
 return k;
 }

 bool Delete_Grades(int n) { 
	 vector<int>::iterator find_n=find(Grades.begin(),Grades.end(),n);
	
 
	 if (find_n!=Grades.end() ) {
		 Grades.erase(remove(Grades.begin(),Grades.end(),n),Grades.end());
		 return true;
	 }
	 else 
		 return false;
 }

 bool operator<=( Student& cstud) { return cstud.Average_Grades() <= Average_Grades();}

 friend ostream& operator<<(ostream& os,const Student& cstud) {
	 if (&os==&cout)  os<<"\nStudent name: ";
		 os<<cstud.st_name<<' ';
			if (&os==&cout) os <<"\nNumber of Grades: ";
			os<<cstud.Grades.size()<<' ';
			 if (&os==&cout) os<<"\nGrades: ";
		 
 for (int i=0;i< cstud.Grades.size();i++)
	 os<<cstud.Grades[i]<<" ";
	 
 return os;
 }

 friend istream& operator>>(istream& os,Student& cstud) { 
	 int count,temp;
	
if (&os==&cin)  cout<<"\n\nEnter student name: ";
 os>>cstud.st_name;
 if (&os==&cin) cout<<"\nEnter the number of grades: "; 
 os>>count;
 if (&os==&cin) cout<<"\nEnter Grades:\n";
  cstud.Grades.clear();
 for(int i=0;i<count;i++) {
os>>temp; 
if ( temp>1 && temp<7) 
	cstud.Grades.push_back(temp);
 else throw ("\nWrong input!\n");
 }
	 
	 
 return os;
}

 bool is_Good() { 
	 vector<int>::iterator Ffind=find(Grades.begin(),Grades.end(),2);
	 if ( Average_Grades() >= 4.50 && Ffind==Grades.end() ) 
		 return true;
	 else 
		 return false;
 }

 void print() const { cout<<"\nStudent name: "<<st_name<<"\nNumber of grades: "<<Grades.size()<<"\nGrades: "; 
 for(auto i=Grades.begin();i!=Grades.end();++i) 
	 cout<<*i<<' ';
 }

bool count_worst_rate(Student& cstud) {
	 vector<int>::iterator find_2=find(cstud.Grades.begin(),cstud.Grades.end(),2);
	 if ( find_2 !=cstud.Grades.end()) 
	 {++count; return true; }
	 else 
		 return false;
 
 }

	void print_AV_GR(int& sum_gr) { cout<<endl<<st_name<<" has a sum of Grades: "<<Sum_of_Grades(sum_gr)<<" with average score of: "<<Average_Grades()<<endl; }
 
};
 
int Student::count=0;



class Group  {
 int gr_num;
 list<Student>stud;
public:
	Group()  {} 
		Group (const  string& st_name_students)     { 
	try {
		ifstream file_students(st_name_students);
		
		
		if ( file_students) {
			 file_students>>gr_num;
			Student temp;
			while (file_students >> temp) 
			stud.push_back(temp);
				
		
		file_students.close();
		} else throw ("\nFile can't open!\n "); 
		} catch (...)
	{ cout<<"\nFile can't open!\n "; }

		}
	

	ostream& Output(ostream& os,const Group& grp) {

		if (&os==&cout) os<<"\nGroup: ";
		os<<grp.gr_num<<' ';
		if (&os==&cout) os<<"\nList of all students :  ";
		for(auto i=grp.stud.begin();i!=grp.stud.end();++i) os<<*i<<' ';
		return os; }
	
	 friend ostream& operator<<(ostream& os,const Group& grp) {
	if (&os==&cout) os<<"\nGroup: ";
		os<<grp.gr_num<<' ';
		if (&os==&cout) os<<"\nList of all students :\n  ";
		for(auto i=grp.stud.begin();i!=grp.stud.end();++i) os<<*i<<' ';
		return os; }

	 

	friend istream& operator>>(istream& os,Group& grp) { 
		Student temp;
	if (&os==&cin) cout<<"\nEnter group number: ";
	os>>grp.gr_num;
if (&os==&cin) cout<<"\nList of students:\n";

while ( os >> temp && grp.stud.size() <5) grp.stud.push_back(temp);
	
 
	return os;
	}

	list<Student> Correction() { 
		list<Student>result;
		Student temp;
		vector<int>grade;
		
		for(auto i=stud.begin();i!=stud.end();++i) {
			temp = * i;
		grade = temp.getGrades();
		vector<int>::iterator find_2=find(grade.begin(),grade.end(),2);
		if (find_2!=grade.end())
		{ result.push_back(temp); }
		}

		return result;
	}

	

};


	


int main()
{
	vector<int>gr1,gr2,gr3=gr1;
	 gr1.assign(3,4);
	 gr1.push_back(6);
		
	for (int j=2;j<=6;j++) {  
	if ( j==5) gr2.push_back(j);
	else gr2.push_back(j);
}
	gr2.resize(5,3);

	
	
	for (int i=2;i<=6;i++) { 
		if ( i==6 ) gr3.assign(2,i);
		else gr3.push_back(i);
	}
	
	gr3.push_back(4);
	

	vector<int>gr4=gr1;
	gr4=gr2;
	gr4.pop_back();
	gr4.resize(8,4);
	gr4.pop_back();
	gr4.pop_back();

	

	Student stud1("Andrei",gr2),stud2("Ivan",gr1),stud3("Emil",gr2),stud4("Elena",gr3),stud5("Alex",gr4);
	cout<<"\nStudents :\n----------------------------------\n ";
	cout<<stud1<<endl<<stud2<<endl<<stud3<<endl<<stud4<<endl<<stud5;
	cout<<'\n';

 int sum1(0),sum2(0),sum3(0),sum4(0),sum5(0);
 int result=stud1.Sum_of_Grades(sum1),
	 result2=stud2.Sum_of_Grades(sum2),
	 result3=stud3.Sum_of_Grades(sum3),
	 result4=stud4.Sum_of_Grades(sum4),
	 result5=stud5.Sum_of_Grades(sum5);
 	


stud1.print_AV_GR(result);
stud2.print_AV_GR(result2);
stud3.print_AV_GR(result3);
stud4.print_AV_GR(result4);
stud5.print_AV_GR(result5);
	





				    list<Student>list_of_stud;
					list_of_stud.push_back(stud1);
					list_of_stud.push_back(stud2);
					list_of_stud.push_back(stud3);
					list_of_stud.push_back(stud4);
				    list_of_stud.push_back(stud5);
			
				
list<Student>::iterator list_it= list_of_stud.begin();

 ofstream ofile("Students.txt");
 if ( ofile.is_open()) {
 ofile<<2<<' ';

 for(list_it;list_it!=list_of_stud.end();++list_it)
  ofile<<*list_it; 
 } else throw ("\nFile can't open!\n");

 ofile.close();

  Group grp("Students.txt");
 cout<<"\n\n\nOutput of group:\n";
 grp.Output(cout,grp);



 ofstream ofile2("Group.txt");
 ofile2<<grp;
 ofile2.close();

 list<Student> st_of_bad_grades;
 
 st_of_bad_grades=grp.Correction();
 cout<<"\n\nList of all  students with a bad grade: ";
 for(auto i=st_of_bad_grades.begin();i!=st_of_bad_grades.end();++i)
	 cout<<*i;

 cout<<'\n';system("pause");return 0;
}
