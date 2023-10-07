#include<iostream>
#include<list>
#include<string>
#include<exception>
#include<algorithm>
#include<fstream>

using namespace std;


class CStudent {
	string stud_Facil_num;
	double stud_Grade;
public:
	CStudent(): stud_Grade(0.) {stud_Grade=0.;}
	CStudent(const string& arg_fn,double arg_grade) : stud_Facil_num(arg_fn),stud_Grade(arg_grade) {}
	CStudent(const CStudent& cstud) : stud_Facil_num(cstud.stud_Facil_num),stud_Grade(cstud.stud_Grade) {}
	string get_Facility_num() { return stud_Facil_num; }
	double get_Grade() { return stud_Grade; }
	void set_Facility_num(const string& arg_fac_n) { stud_Facil_num=arg_fac_n; }
	void set_Grade(double arg_grade) { stud_Grade=arg_grade; }

	friend ostream& operator<<(ostream& os,const CStudent& cstud) {
		if (&os==&cout) os<<"\nFacility number: ";
		os<<cstud.stud_Facil_num<<' ';
		if (&os==&cout) os<<"\nGrade: ";
		os<<cstud.stud_Grade<<' ';
		return os;
	}

	friend istream& operator>>(istream& os,CStudent& cstud) {
		if (&os==&cin) cout<<"\nEnter facility number: ";
		os>>cstud.stud_Facil_num;
		if (&os==&cin) cout<<"\nEnter grade: ";
		os>>cstud.stud_Grade;
		return os;
	}
	CStudent& operator=(const CStudent& cstud) {
		stud_Facil_num = cstud.stud_Facil_num;
		stud_Grade = cstud.stud_Grade;
		return *this;
	}

};

class CStudentBook {
	CStudent Student;
	list<string>List_of_disciplines;
	list<int>List_of_points;

	list<int>calcScoresInt() {
		list<int>Result;
		list<int>::iterator iiter=List_of_points.begin();
		for(iiter;iiter!=List_of_points.end();++iiter) {
			
			 if ( *iiter >= 50 && *iiter < 60 )
				Result.push_back(3);

			else if ( *iiter >= 60 && *iiter < 75 )
				Result.push_back(4);

			else if ( *iiter >= 75 && *iiter < 89 )
				Result.push_back(5);

			else if ( *iiter >= 89)
				Result.push_back(6);

			else Result.push_back(2);
		}

		return Result;

	}
public:
	CStudentBook(const CStudent& arg_cstud) : Student(arg_cstud) {
		List_of_disciplines.push_back("Object Oriented Programming");
		List_of_points.push_back(0);
		List_of_disciplines.push_back("Synthesis for algorithms");
		List_of_points.push_back(0);
		List_of_disciplines.push_back("Mathematics");
		List_of_points.push_back(0);
		List_of_disciplines.push_back("English");
		List_of_points.push_back(0);
		List_of_disciplines.push_back("Computer science");
		List_of_points.push_back(0);
	}
	CStudentBook(const string& filename ) {
		ifstream ifile(filename.c_str());

		try {
			if (ifile.is_open()) {
				string strtemp;
				int itemp;
				ifile >> Student;
				while ( ifile >> strtemp >> itemp) 
				{List_of_disciplines.push_back(strtemp);List_of_points.push_back(itemp);}
				 
			} else throw("\nCan't open file!");
		}catch(exception& e) { cout<<endl<<e.what()<<endl; }
	}

	ostream& Output(ostream& os) {
		os<<"\nStudent info:\n";
		os<<Student;
		os<<"\nList of disciplines and their points: ";
		auto strindex=List_of_disciplines.begin();
		auto iindex=List_of_points.begin();
		for (;strindex!=List_of_disciplines.end(),iindex!=List_of_points.end();++strindex,++iindex)
			os<<*strindex<<"  "<<*iindex<<endl;
		
		return os;
	}

	list<int>::iterator getMaxPoint() {
		auto Result = max_element(List_of_points.begin(),List_of_points.end());
		return Result;
	}
	list<int>::iterator getMinPoints() {
	auto Result = min_element(List_of_points.begin(),List_of_points.end());
		return Result;}

	void addPoints(const string& subject,int pnt) {
		int count=0;
		list<string>::iterator find_subj = find(List_of_disciplines.begin(),List_of_disciplines.end(),subject),
			striter=List_of_disciplines.begin();
		list<int>::iterator iiter = List_of_points.begin();
		while ( striter != find_subj) {
			striter++;
			count++;
		}

		if ( find_subj!=List_of_disciplines.end()) {
			advance(iiter,count);
			
			List_of_points.insert(iiter,pnt);
			List_of_points.erase(iiter);
		}
	}


	double getAverageScore() {
		double Result=0.;
		list<int>Grades = calcScoresInt();
		for(auto index=Grades.begin();index!=Grades.end();++index) 
			Result+=*index;

		Result/=Grades.size();

		Student.set_Grade(Result);

			return Result;
	}

	friend ostream& operator<<(ostream& os,const CStudentBook& cstudbook) {
		if (&os==&cout) os<<"\nStudent info:";
		os<<cstudbook.Student;
		if (&os==&cout) os<<"\nList of disciplines and their points:\n";
		auto strindex=cstudbook.List_of_disciplines.begin();
		auto iindex=cstudbook.List_of_points.begin();
		os<<endl;
		while ( strindex!=cstudbook.List_of_disciplines.end() && iindex!=cstudbook.List_of_points.end() ) 
			os<<*strindex++<<' '<<*iindex++<<endl;
		
		return os;
	}

	friend istream& operator>>(istream& os,CStudentBook& cstudbook) {
			string strtemp;
		int itemp;

		if (&os==&cin) cout<<"\nEnter student info: ";
		os>>cstudbook.Student;

	if (&os==&cin) cout<<"\nList of disciplines:\nEnter 5 disciplines and their points:\n";
	cstudbook.List_of_points.clear();
		cstudbook.List_of_disciplines.clear();
		
	
		while (/*cstudbook.List_of_points.size() != 5 &&*/ os >> strtemp >> itemp ) { 
			
			cstudbook.List_of_disciplines.push_back(strtemp);
			cstudbook.List_of_points.push_back(itemp); 
		}

		return os;
	}



	
};


int main()
{
	const string filename("Student's book.txt"),
		Subject1("Synthesis for algorithms"),Subject2("Object Oriented Programming"),Subject3("English"),Subject4("Computer science"),Subject5("Mathematics");
	CStudent stud1("19621609",4.34);
	CStudentBook obj1(stud1);
	
	obj1.addPoints(Subject4,59);
		obj1.addPoints(Subject1,66);
		obj1.addPoints(Subject3,67);
			obj1.addPoints(Subject2,88);
		obj1.addPoints(Subject5,55);
	
	
	cout<<obj1;
	
	cout<<"\n\nAverage score is: "<<obj1.getAverageScore()<<endl;
	cout<<obj1;

	cout<<"\n\nMaximum points: "<<*obj1.getMaxPoint()<<endl
		<<"\n\nMinimum points: "<<*obj1.getMinPoints()<<endl;

	ofstream ofile(filename.c_str());

	if ( ofile.good()) 
		ofile<<obj1;
	 else throw("\nCan't open file!\n");
ofile.close();

CStudentBook obj2(filename.c_str());
cout<<obj2;


	
	cout<<endl;system("pause");
	return 0;
}


