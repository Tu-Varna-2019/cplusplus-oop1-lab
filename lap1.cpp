#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<time.h>
#include<algorithm>
#include<iterator>
#include<fstream>
using namespace std;

void output(vector<int>&v,ostream& os) {
	
	for(auto j=v.begin();j!=v.end();++j) {
		if ( j==v.end()-1) os<<*j;
		else
		os<<*j<<',';
	}
	cout<<" }\n\n";
	for(int i=0;i<80;i++) cout<<'-';
	
}

void delel(vector<int> &v, int n) {
	v.erase(v.end()-n);
}

int main()
{
	srand(time(NULL));
	vector<int>v1;
	int i=0;
	while ( i < 20) {
		v1.push_back(rand()%50+1);
		i++;
	}

	cout<<"\nAll numbers,that exist in v1: { ";output(v1,cout);
	
	vector<int>v2;
	
	for(auto j=v1.begin();j!=v1.end();j++) {
		
		if ( *j %2==0) { v2.push_back(*j); v1.erase(j);j=v1.begin();}
	}


	cout<<"\n\nElements of v1 without even numbers: {"; output(v1,cout);
		
		cout<<"\n\nElements of v2: { "; output(v2,cout);
		

		if (v1.size()>=3)  v1.insert(v1.begin()+3,3,5);
		
		else cout<<"\n\nv1 has less than 3 elements! ";


		cout<<"\n\nElements of v1 with added 5 elements after 3rd position: { "; output(v1,cout);

		

		int temp=v1.at(v1.size()-2),temp2=v1.at(v1.size()-3);
		cout<<"\n\nRemoved elements: "<<temp<<','<<temp2;
		delel(v1,2);
		delel(v1,2);
	


		cout<<"\n\nElements of v1 without the elements,that are before the last one and the one before that:\n{ "; output(v1,cout);

		sort(v2.begin(),v2.end());

		cout<<"\n\nSorted elements of v2: { "; output(v2,cout);
		

		fstream vec_files;
		vec_files.open("Vectors.txt",ios::binary | ios::out);
		output(v1,vec_files);
		if (vec_files.good()) cout<<"\n\nWriting on vector v1 has been sucsessful!";
		output(v2,vec_files);
			if (vec_files.good()) cout<<"\n\nWriting on vector v2 has been sucsessful!";
		vec_files.close();
	

		vector<int>::iterator max1=v1.begin(),max2=v2.begin();
		for(auto i=v1.begin();i!=v1.end();++i)
		{ if ( *max1 <= *i) max1=i; }
		for(auto i=v2.begin();i!=v2.end();++i)
		{ if ( *max2 <= *i) max2=i; }
		cout<<"\n\nThe total maximum element of vectors v1 and v2 is : "; if ( *max1 > *max2) cout<<*max1; else cout<<*max2; 
		
	


	cout<<'\n';system("pause");return 0;
}