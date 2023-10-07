#include<iostream>
#include<set>
#include<exception>
#include<string>
#include<time.h>
#include<iterator>
#include<algorithm>
#include<sstream>

using namespace std;


void toto2(set<int>&t) {

	while ( t.size() != 6 ) 

	t.insert(rand()%44+6);

	
	
}

void toto1(set<int>&t) {

	while ( t.size() != 6 ) 
	t.insert(rand()%49+1);

}




void print(set<int>& s)  {
	set<int>::iterator iter = s.begin();
	while ( iter != s.end())   cout<<"Number:"<<'\t'<<*iter++<<endl;  
}



int main()
{
	srand(time(NULL));
	set<int>My_Coupon_1;
	set<int>My_Coupon_2;
	set<int>Circulation;
	toto2(My_Coupon_1);
	toto2(My_Coupon_2);
	toto1(Circulation);
	cout<<"\nCoupon 1 :\n\n";print(My_Coupon_1);
	cout<<"\n\nCoupon 2 :\n\n";print(My_Coupon_2);
	cout<<"\nCirculation's numbers:\n\n";print(Circulation);

	
	cout<<"\n\nNumber of matches in coupon 1: ";
	set_intersection(Circulation.begin(),Circulation.end(),My_Coupon_1.begin(),My_Coupon_1.end(),ostream_iterator<int>(cout," "));
	cout<<"\n\nNumber of matches in coupon 2: ";
	set_intersection(Circulation.begin(),Circulation.end(),My_Coupon_2.begin(),My_Coupon_2.end(),ostream_iterator<int>(cout," "));

	
	



	



	cout<<'\n';system("pause");return 0;
}