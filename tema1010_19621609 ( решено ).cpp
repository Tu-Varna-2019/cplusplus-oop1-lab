#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<iterator>
#include<fstream>
#include<exception>
#include<sstream>
using namespace std;

void lines() {
	for (int i=0;i<30;i++)
		cout<<'-';
}

class CPerson {
	string pers_Name,pers_EGN;
	public:
		CPerson () {}
		CPerson(const string& arg_pers_EGN,const string& arg_pers_Name) : pers_Name(arg_pers_Name),pers_EGN(arg_pers_EGN){}

		friend bool operator < ( const CPerson& cpersL,const CPerson& cpersR) { 
			
			return cpersL.pers_EGN < cpersR.pers_EGN; 
		
		}

	friend bool operator == ( const CPerson& cpersL,const CPerson& cpersR ) { 
		return cpersL.pers_EGN == cpersR.pers_EGN ;
	}

		

		friend ostream& operator<<(ostream& os,const CPerson& cpers) {
		
		if (&os==&cout) os<<"EGN: ";
		
	
		
			os<<cpers.pers_EGN<<' ';

				if (&os==&cout) os<<"\nName:";
			os<<cpers.pers_Name<<endl;
			
			return os;
		}
		friend istream& operator>> (istream& os,CPerson& cpers) {
			
			if (&os==&cin) cout<<"\nEnter EGN: ";
			os>>cpers.pers_EGN;
			if (&os==&cin) cout<<"\nEnter name: ";
			os >> cpers.pers_Name;


			return os;
		}

		string get_Name() { return pers_Name; }
		string get_EGN() { return pers_EGN; }
		void set_Name(const string& arg_name) { pers_Name=arg_name; }
		void set_EGN(const string& arg_EGN) { pers_EGN=arg_EGN; }
};

class CCity {
	string city_Name;
	vector<CPerson> city_People;
public:
	CCity(const string& name_file) {
		try {
		ifstream ifile(name_file);
		if ( ifile.good() ) {
			ifile>> city_Name;
		
		CPerson temp;
		
		while ( ifile >> temp) 
			city_People.push_back(temp);

		}
		else
			throw ("\nCan't open file!");
		ifile.close();
		} catch( exception& e) { cout<<endl<<e.what()<<endl; }
	}

	ostream& Output(ostream& os,const CCity& city) {
		if (&os==&cout) os<<"\nCity: ";
		os<<city.city_Name<<' ';
		if (&os==&cout) os<<"\nList of people:\n";
		for ( auto pers_iter=city.city_People.begin();pers_iter!=city.city_People.end();++pers_iter) 
			os<<*pers_iter<<' ';

		return os;
	}

	friend ostream& operator<<(ostream& os,const CCity& city) {
		if (&os==&cout) os<<"\nCity: ";
		os<<city.city_Name<<' ';
	
		if (&os==&cout) os<<"\nList of people:\n";
		for ( auto pers_iter=city.city_People.begin();pers_iter!=city.city_People.end();++pers_iter) 
			os<<*pers_iter<<' ';

		return os;
	}

	friend istream& operator >> (istream& os,CCity& city) {
		CPerson temp;
		if (&os==&cin) cout<<"\nEnter name of city: ";
		os >> city.city_Name;

		if (&os==&cin) cout<<"\nList of people:\n";
		city.city_People.clear();
		while ( os >> temp) {  city.city_People.push_back(temp);  }

		return os;
	}


	vector<CPerson> get_identical_EGN() {

		vector<CPerson> Result;
		vector<CPerson>::iterator itr1;
		sort(city_People.begin(),city_People.end());
		itr1 = unique(city_People.begin(),city_People.end());
		Result.push_back(*itr1);

		/*vector<CPerson>::iterator Result;
		
		
		Result = adjacent_find(city_People.begin(),city_People.end(),equal_to<CPerson>());
		cout<<"\n\nDistance: "<<distance(city_People.begin(),city_People.end())<<endl;*/

		return Result;
	}

	void  remove_identical_EGN() {

		sort(city_People.begin(),city_People.end());
	
		city_People.erase( unique(city_People.begin(),city_People.end() ) , city_People.end() ) ;
	}

	
	void remove_Vector(vector<CPerson>& arg_city_people) {
	
		for (auto index=arg_city_people.begin();index!=arg_city_people.end();++index) {

		vector<CPerson>::iterator Find = find(city_People.begin(),city_People.end(),*index);

		if ( Find != city_People.end() ) city_People.erase(Find);
		}
	}


};



int main()
{
	CPerson pers1("9809120220","Andrei"),pers2("0001032341","Elena"),pers3("0102030405","Alex"),pers4("9709883254","Nelina"),pers5("9912964291","Yavor");
	CPerson dupl("0001032341","Clone");
	cout<<"\nList of people:\n----------------------------------\n"
		<<pers1<<endl<<pers2<<endl<<pers3<<endl<<pers4<<endl<<pers5<<endl<<dupl<<"\n\n\n";

	vector<CPerson> list_of_people1,list_of_people2,temp;

	
list_of_people1.push_back(pers1);
list_of_people1.push_back(pers2);
list_of_people1.push_back(pers3);
list_of_people1.push_back(pers4);
list_of_people1.push_back(dupl);
sort(list_of_people1.begin(),list_of_people1.end());

list_of_people2.push_back(pers5);
cout<<endl;


CPerson find_EGN("0102030405","");
bool print_NF = true;
cout<<"\n\nFinding a person based on EGN :"<<find_EGN.get_EGN()<<endl;
for (auto index=list_of_people1.begin();index!=list_of_people1.end();++index) {
	if ( *index == find_EGN) { cout<<"\nThere is a match of the EGN with the following person: "<<*index<<endl;print_NF=false; }	
}

if ( print_NF)  cout<<"\nThere is no match to a person with the following EGN:  "<<find_EGN.get_EGN()<<endl;
	ofstream ofile1("People 1-4.txt");
	if ( ofile1.is_open()) {
		ofile1 <<"Varna\n";
	
		for ( auto index=list_of_people1.begin();index!=list_of_people1.end();++index)
			ofile1<<*index;
	}
	else throw ("\nFile cannot open! ");
	ofile1.close();

	ofstream ofile2("Person 5.txt");
	if ( ofile2.is_open()) {
		ofile2 <<"Sofia\n";
		for ( auto index=list_of_people2.begin();index!=list_of_people2.end();++index)
			ofile2<<*index;
	}
	else throw ("\nFile cannot open! ");
	ofile2.close();

CCity city1("People 1-4.txt"),city2("Person 5.txt");
cout<<"\n---------------------\nPeople in Varna:\n"<<city1;
cout<<"\n---------------------\nPeople in Sofia:\n"<<city2;
lines();
vector<CPerson> Res= city1.get_identical_EGN();
cout<<"\n\nIdentical EGN:\n";
vector<CPerson>::iterator iter2 = Res.begin();
while ( iter2 != Res.end()) cout<<*iter2++<<' ';
lines();
city1.remove_identical_EGN();
cout<<"\n\nCity with people,that have unique EGN:\n";
cout<<city1;
lines();
vector<CPerson> VecRemove;
VecRemove.push_back(pers1);
VecRemove.push_back(pers2);
vector<CPerson>::iterator iter=VecRemove.begin();

city1.remove_Vector(VecRemove);

cout<<"\n\nRemoved people of Varna:\n\n";
while ( iter!=VecRemove.end()) cout<<*iter++<<' ';
lines();
cout<<"\n\nCurrent population of Varna:\n"<<city1;



	cout<<'\n';system("pause");return 0;
}