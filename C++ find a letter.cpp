#include <iostream>
#include <string>
#include<list>
#include<string>
#include<algorithm>
#include<iterator>
#include<sstream>
using namespace std;

	
		
	


int main()
{
	list<string>str_List(1,"I am typing exactly 10 words for testing compiler c++.");
	list<string>::iterator index=str_List.begin();
	cout<<"Elements of list: ";
	cout<<*index;
	cout<<endl;


	string str=*index,temp,result,result2;
	stringstream iss(str);


	while (iss>> temp) {
			size_t Ffind= temp.find('c');
		if (Ffind !=string::npos) result+=temp+' ';
		if ( temp.size()==4) result2+=temp+' ';
	}
		cout<<"\n\nAll strings,that  contain the letter c: "<<result;
		cout<<"\n\nAll strings with size of 4: "<<result2;
		

		
	
cout<<endl;system("pause");
return 0;
}