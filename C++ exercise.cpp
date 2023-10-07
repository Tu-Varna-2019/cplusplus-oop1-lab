#include<iostream>
#include<algorithm>
#include<fstream>
#include<list>
#include<vector>
#include<map>
#include<string>
#include<iterator>
#include<exception>

using namespace std;

class CStudent {
	string fn,group;
public:
	CStudent() {}
	CStudent(const string& argFN,const string& argGROUP) : fn(argFN),group(argGROUP) {}

	string getFN() const { return fn; }
	string getGRP() const { return group; }

	friend istream& operator>>(istream& os,CStudent& stud) {
		if (&os==&cin) cout<<"\nEnter facility num: ";
		os>>stud.fn;

		if (&os==&cin) cout<<"\nEnter group: ";
		os>>stud.group;

		return os;
	}

	friend ostream& operator<<(ostream& os,const CStudent& stud ) {

if (&os==&cout) os<<"\nFacility num: ";
os<<stud.fn<<' ';

if (&os==&cout)  os<<"\nGroup: ";
os<<stud.group<<' ';

return os;

	}

	const bool operator< (CStudent& stud) {
		return getFN() < stud.getFN(); }

};

class Specialty {
	string spName;
	vector<CStudent>vstud;
public:
	Specialty() {}
	Specialty(const string& argSPName) : spName(argSPName) {}

	string getName() const { return spName; }

	vector<CStudent> getVStud() const { return vstud; }

	void setName(const string& argspName) { spName=argspName; }
	void setVstud(const vector<CStudent>& argvstud) { vstud=argvstud; }
	void SortBYFN() {
		sort(vstud.begin(),vstud.end());
	}

	bool operator==(Specialty& stud) {
		return getName() == stud.getName(); }

	bool operator<(Specialty& stud) {
		return getName() < stud.getName(); }

	friend istream& operator>>(istream& os,Specialty& spec) {
		if (&os==&cin) cout<<"\nEnter Name of specialty: ";
		os>>spec.spName;

		int count;
		if (&os==&cin) cout<<"\nEnter number of students: ";
		os>>count;

		if (&os==&cin) cout<<"\nVector of students: ";
		spec.vstud.clear();

		CStudent temp;
		int i=0;
		while (  i < count && os >> temp) {
			spec.vstud.push_back(temp);
			i++;
		}

		return os;

	}

	friend ostream& operator<<(ostream& os,const Specialty& spec ) {

if (&os==&cout) os<<"\nName of specialty: ";
os<<spec.spName<<' ';

if (&os==&cout) os<<"\nNumber of students: ";
os<<spec.vstud.size()<<' ';

if (&os==&cout) os<<"\nVector of students: ";

//for(auto const index : spec.vstud)
//	os<<index<<' ';

ostream_iterator<CStudent> it(os," ");

copy(spec.vstud.begin(),spec.vstud.end(),it);

return os;

	}



};

class Discipline {
	string disName;
	vector<Specialty>vspec;
public:

	Discipline(const string& file_name) {

		try {

		ifstream ifile(file_name.c_str());

		if ( ifile.good()) {

			ifile>>disName;

			Specialty temp;

			while ( ifile >> temp) 
				vspec.push_back(temp);

		}else throw("\nError!\nCan't open file!");

		}catch(exception& e) { cout<<e.what()<<endl; }

	}

	string getDisName() const { return disName; }

	void setDisName(const string& argdisName) { disName=argdisName; }

	vector<Specialty> getVspec() const { return vspec; }

	map<string,list<string>> getSpec_GRP() {
		map<string,list<string>> result;

		vector<Specialty>::iterator iter = vspec.begin();

		while ( iter != vspec.end()) {
			vector<CStudent> stud= iter->getVStud();
			vector<CStudent>::iterator it = stud.begin();
				list<string> lGRP;
				while ( it!=stud.end()) {
					lGRP.push_back(it->getGRP());
					it++;
				}
				result.insert(make_pair(iter->getName(),lGRP));
					iter++;
					
				
				
		}
	
		return result;

	}

	list<string> getListFN(const string& name_spec,const string& grp ) {
		list<string> result;

		vector<Specialty>::iterator iter = vspec.begin();
	while ( iter != vspec.end()) {
		if ( iter->getName() == name_spec) {
			vector<CStudent> stud= iter->getVStud();
			vector<CStudent>::iterator it = stud.begin();

			while ( it != stud.end()) {
			if ( it->getGRP() == grp) 
				result.push_back(it->getFN());
			it++;
			}
			
		}
			iter++;
			
		
	}

		return result;
	}

	friend istream& operator>>(istream& os,Discipline& dis) {
		if (&os==&cin) cout<<"\nEnter name of discipline: ";
		os>>dis.disName;

		if (&os==&cin) cout<<"\nVector of specialtites: ";

		dis.vspec.clear();

		Specialty temp;

		while ( os >> temp)
			dis.vspec.push_back(temp);

		return os;

	}

	friend ostream& operator<<(ostream& os,const Discipline& dis) {
		if (&os==&cout) os<<"\nName of discipline: ";
		os<<dis.disName<<' ';

		if (&os==&cout) os<<"\nVector of specialties: ";

		/*for(auto const& iter : dis.vspec)
			os<<iter<<' ';
*/
		ostream_iterator<Specialty> iter(os," \n");

		copy(dis.vspec.begin(),dis.vspec.end(),iter);

		return os;
	}

};


int main()
{
	const string file_name("Discipline.txt");
	CStudent stud1("19532354","grp2"),stud2("19346523","grp1"),stud3("19346545","grp2"),stud4("19742353","grp3"),stud5("195454545","grp1"),stud6("194343434","grp1"),stud7("2382323","grp2"),
		stud8("3483473","grp1"),stud9("2323232","grp3");
	CStudent arr[]= { stud1,stud2,stud3,stud9};
	CStudent arr1[] = {stud4,stud5,stud6,stud7,stud8 };


	vector<CStudent> vST,vST2;
	for(int i=0;i<4;i++)
		vST.push_back(arr[i]);

	for(int i=0;i<5;i++)
		vST2.push_back(arr1[i]);


	Specialty sp1("KST"),sp2("SIT");
	sp1.setVstud(vST);
	sp2.setVstud(vST2);
	

	ofstream ofile(file_name.c_str());

	if ( ofile.is_open()) {

	ofile<<"Science\n";

	
		ofile<<sp1<<endl;

	
		ofile<<sp2<<endl;

	}else throw("\nError!");

	ofile.close();




	


	Discipline obj(file_name);
	cout<<obj;

	list<string>FNSIT= obj.getListFN("SIT","grp1");

	cout<<"\nList of facility number of SIT in grp1:\n";
	for (auto const& index: FNSIT)
		cout<<index<<" , ";

	map<string,list<string>>Map = obj.getSpec_GRP();

	cout<<"\nMap of specialty and their list of groups:\n";
	for(map<string,list<string>>::iterator iter=Map.begin();iter!=Map.end();++iter) {
		for (auto const& index : iter->second )
		cout<<iter->first<<' ' <<index<<endl;
	}
	

	cout<<'\n';system("pause");return 0;
}