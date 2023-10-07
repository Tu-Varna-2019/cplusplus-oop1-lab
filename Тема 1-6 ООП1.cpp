#include <iostream>
#include <string>
#include<sstream>
#include<fstream>
using namespace std;

enum Gender { male=1,female,other,unspecified};




class CPerson {
protected:


	string name,egn;
	Gender gend;

		void getYMD(const string& _egn,int Year,int Month,int Day) const { 

 
  char* ch=new char[_egn.length()];

  for(int i=0;i<_egn.length();i++) 
  ch[i]=_egn.at(i);
  
  
  
  string temp;
  for(int j=0;j<2;j++)
temp.push_back(ch[j]);

string temp2;
for(int k=2;k<4;k++)
temp2.push_back(ch[k]);

string temp3;
for(int m=4;m<6;m++)
temp3.push_back(ch[m]);

stringstream(temp)>>Year;
stringstream(temp2)>>Month;
stringstream(temp3)>>Day;

Year+=1911;
delete[]ch;
}
	
	public:
		
 ostream& Output(ostream& os) {string temp=SetGender(gend); os<<"\nName: "<<name<<"\nEGN: "<<egn<<"\nGender: "<<temp;return os;}
	void SetName(const string& str) { name=str;}
	
	void SetEGN(const string& str) {
		egn=str;}
		


		string SetGender( Gender gen) {
			
			switch(gen) { 
			case 1: 
				return "male";break; 
			case 2: return "female";break;
			case 3: return "other ";break;
			default:
				return "N/A";break;
			
					 }
		}

		string GetName() const{ return name;}
		
		string GetEGN()const { return egn;}
		
		
	CPerson() : name("N/A"),egn("8888"),gend(){}
	
	
	CPerson(const string& _name,Gender _gend,const string& _egn="8888") : name(_name),gend(_gend),egn(_egn){}
	
	bool isValid(const string& strEGN) { if ( strEGN.size() == 10) return true; 
	else
	return false; }

	friend ostream& operator<<(ostream&os,const CPerson& pers) {
	os<<"\nName: "<<pers.name<<"\nEGN: "<<pers.egn<<"\nGender: "<<pers.gend;return os;} 


	friend istream& operator>>(istream& os,CPerson& pers) { if ( os==&cin)  os.ignore();
	cout<<"\n\nEnter name: ";getline(os,pers.name);
	cout<<"\nEnter EGN: ";getline(os,pers.egn);
	cout<<"\nEnter gender:\n--male--\n--female--\n--other--\n "; string temp;
	getline(os,temp);
	if ( temp=="male") pers.SetGender(male);
	else if ( temp=="female") pers.SetGender(female);
	else if ( temp=="other") pers.SetGender(other);
	else pers.SetGender(unspecified);
	return os;
	
	}


};







	class CAddress:public CPerson {
	
		string street,pcode,town;
	public:
		CAddress() : street("N/A"),pcode("N/A"),town("N/A"){}
		CAddress(const string&_street,const string&_pcode,const string&_town): street(_street),pcode(_pcode),town(_town){}
		CAddress(const CAddress& adr) { street=adr.street;pcode=adr.pcode;town=adr.town;}
		ostream& Output(ostream& os) {os<<"\nStreet: "<<street<<"\nPostal code: "<<pcode<<"\nTown: "<<town;return os;}

		friend ostream& operator<<(ostream& os,const CAddress& addr) { os<<"\nStreet: "<<addr.street<<"\nPostal code: "<<addr.pcode<<"\nTown: "<<addr.town;return os;}

		friend istream& operator>>(istream& os,CAddress& addr) { if (os ==&cin) os.ignore();cout<<"\n\nEnter street: ";
		                                                                          getline(os,addr.street);cout<<"\nEnter postal code: ";
																				  getline(os,addr.pcode);cout<<"\nEnter town: ";
																				  getline(os,addr.town);
																		return os; }
	};


	class CGSM {
	protected:
		string model;
		int tarrif_plan;
		CGSM() : model("N/A") , tarrif_plan(NULL){}
		CGSM(const string& _model,int _tarrif_plan) : model(_model),tarrif_plan(_tarrif_plan){}
	public:
		ostream& OutputTarrifPlan(ostream& os) { os<<tarrif_plan;return os;}


		virtual ostream& OutputGSM(ostream& os ) const = 0;
virtual string GetCGSMNumber() const = 0;
virtual istream& InputGSM(istream& os) = 0;
 istream& operator>> (istream& os) {if (os==&cin)  os.ignore();cout<<"\nEnter a model of phone: ";getline(os,model);cout<<"\nEnter a tarrif plan: ";
os>>tarrif_plan;return os;}
	};




	class CStudent:public CPerson,public CGSM {
string fn;
CAddress addr;
string phone_num;

bool operator>(const CStudent& stud)const { return (stud.tarrif_plan >tarrif_plan);}

	public:
			static int num_of_stud;
		ostream& OutputGSM(ostream& os) const { os<<"Phone number: "<<phone_num;return os;}
		string GetCGSMNumber() const { return phone_num;}
		istream& InputGSM(istream& os) {if(os==&cin) os.ignore(); getline(os,phone_num);return os;}

		CStudent(): fn("\n8888"),addr(),CPerson(){++num_of_stud;}
		CStudent(const CPerson& pers,const CAddress& _addr) : addr(CAddress(_addr)),CPerson(pers),fn("\n8888"){}
		CStudent(const CPerson& pers,const CAddress& _addr,const string& _fn) : addr(CAddress(_addr)),CPerson(pers),fn(_fn){}

		CStudent(const CStudent& stud) { fn=stud.fn;addr=stud.addr;}
		ostream& Output(ostream& os) { CPerson::Output(os);addr.Output(os);os<<"\nFacility number: "<<fn;return os;}
		void setAddress(const CAddress& _addr) { addr=_addr;}

		void setFN(const string& _fn) { fn=_fn;}


		CAddress getAddress() { return addr;}

		string getFN() { return fn;}

		friend void ConsoleInputEGN(CStudent& stud) { cout<<"\nEnter EGN: ";getline(cin,stud.egn);}

		friend ostream& operator<<(ostream& os,const CStudent& stud) {os<<"\nName"<<stud.name<<"\nEGN: "<<stud.egn<<"\nGender: "<<stud.gend  <<stud.addr<<"\nFacility number: "<<stud.fn;return os;}
		int GetAge(const string& _egn) {
			 char ch[2];
			 int age;
  for(int i=0;i<2;i++) 
	  ch[i]=_egn.at(i);
  
  string temp;
  for(int j=0;j<2;j++)
temp.push_back(ch[j]);
		stringstream(temp)>>age;
		age+=1900;
			return (2020-age);}
		friend bool operator==( CStudent& stud1, CStudent& stud2) { return stud1.GetAge(stud1.GetEGN()) == stud2.GetAge(stud2.GetEGN());}
		friend bool operator!=( CStudent& stud1, CStudent& stud2) { return stud1.GetAge(stud1.GetEGN()) != stud2.GetAge(stud2.GetEGN());}
		friend bool operator<( CStudent& stud1,CStudent& stud2) { return stud1.GetAge(stud1.GetEGN()) < stud2.GetAge(stud2.GetEGN());}
		friend bool operator>=( CStudent& stud1, CStudent& stud2) { return stud1.GetAge(stud1.GetEGN()) >= stud2.GetAge(stud2.GetEGN());}

	



		friend istream& operator>>(istream& os,CStudent& stud) { if (os ==&cin) os.ignore();
		cout<<"\nEnter name: ";os>>stud.name;
		cout<<"\nEnter EGN: ";os>>stud.egn;
		
	os.ignore();
		os>>stud.addr;
			cout<<"\nEnter facility number: ";
		getline(os,stud.fn);
		return os; }


	};


	  int CStudent::num_of_stud=0;


	int main()
	{
		CPerson per1,per2("Ivan",male,"9721100782"),pers3("Martin",male);
		per1.SetName("Pesho");
		per1.Output(cout);
		cout<<endl<<per1.GetName()<<" has: ";
		if ( per1.isValid(per1.GetEGN())) cout<<"Valid egn! ";else cout<<"Invalid egn!";
		cout<<"\n\n\--------------\n\n";
		per2.Output(cout);
		cout<<endl;
		cout<<endl<<per2.GetName()<<" has: ";
		if ( per2.isValid(per2.GetEGN())) cout<<"Valid egn! ";else cout<<"Invalid egn!";
		cout<<"\n\n\--------------\n\n";
		CStudent stud1,stud2(per1,CAddress("Vasil Levski","9000","Varna")),stud3(pers3,CAddress("Bratya Milodinovi","9001","Plovdiv"),"19621654");
		cout<<"Student 1 info: "<<endl;
		stud1.Output(cout);
		cout<<"\n\n\--------------\n\n";
		cout<<"Student 2 info: "<<endl;
		stud2.Output(cout);
		cout<<"\n\n\--------------\n\n";
		cout<<"Student 3 info: "<<endl;
		stud3.Output(cout);

		cout<<"\nEGN on Student 2: ";
		
		ConsoleInputEGN(stud2);
		cout<<"\nEGN on Student 3: ";
	ConsoleInputEGN(stud3);
		bool Compare1=stud2==stud3;
		bool Compare2=stud2!=stud3;
		bool Compare3=stud2< stud3;
		bool Compare4=stud2>=stud3;
		if ( Compare1)
		cout<<"\nStudent 2's age is equal to student 3'rd ";
		else
			cout<<"\nStudent 2's age is NOT equal to student 3'rd ";
		if ( Compare2)
		cout<<"\nStudent 2's age is NOT equal to student 3'rd ";
		else
			cout<<"\nStudent 2's age is  equal to student 3'rd ";
		if ( Compare3)
		cout<<"\nStudent 2's age is less than to student 3'rd ";
		else
			cout<<"\nStudent 2's age is NOT less than   student 3'rd ";
		if ( Compare4)
		cout<<"\nStudent 2's age is greater or equal to student 3'rd ";
		else
			cout<<"\nStudent 2's age is NOT greater or equal to student 3'rd ";

		fstream stud_file;
		stud_file.open("Students.txt",ios::binary | ios::out);

		stud_file<<	stud1<<stud2;

		stud_file.close();
		cout<<"\n------------------------------------------------------------------------------\n";
		cout<<"Exercise 5:\n\n\n";
		CAddress addr;
		CPerson pers4;
		
		
		cout<<"\nSet address information: ";
		cin>>addr;
		cout<<"-------------------------------\n\nSet personal information: ";
		cin>>pers4;
		cout<<"-------------------------------\n\nSet student information: ";
		CStudent stud4;
		cin>>stud4;
		CGSM* stud5=&stud4;
		stud5->operator>>(cin);
		cout<<"\nSet phone number for student: ";cin.ignore();
		stud5->InputGSM(cin);
		
		cout<<"\nYou entered a  ";stud5->OutputGSM(cout);
		CGSM* stud6=new CStudent;
		cout<<"\nEnter information for another student: ";
		stud6->operator>>(cin);
		
		
		bool Compare5 = stud5 > stud6;
		cout<<"\n\nStudent with the following tarrif plan ";stud5->OutputTarrifPlan(cout); cout<<" does ";
		if (Compare5) {
			cout<<"greater tarrif plan than student's other tarrif plan: ";stud6->OutputTarrifPlan(cout); }
		else {
			cout<<"NOT have a greater tarrif plan than student's other tarrif plan: ";stud6->OutputTarrifPlan(cout); }
		


		ifstream Data_base_student;
		Data_base_student.open("Data students.txt",ios::binary | ios::in);


		
		CStudent*Array= new CStudent[CStudent::num_of_stud];

		int index=0;
	
	
		while( index < CStudent::num_of_stud && Data_base_student >> Array[index] ) { Data_base_student.ignore();  index++; }
	
		

		Data_base_student.close();

		delete[]Array;
		
		
		cout<<endl;system("pause");
		
		return 0;
	}
	