#include<iostream>
#include<exception>
#include<string>
#include<iterator>
#include<algorithm>
#include<list>
#include<fstream>
#include<map>
#include<functional>
using namespace std;

class CFile {
	string file_name,file_extension;
public:
	CFile() : file_name("") ,file_extension(".txt") {}
	CFile(const string& arg_name,const string& arg_extension) : file_name(arg_name),file_extension(arg_extension) {}
	string getFileName() { return file_name; }
	string getFileEXN() { return file_extension;}
	void setFileName(const string& arg_name) { file_name=arg_name; }
	void setFileEXN(const string& arg_extension) { file_extension=arg_extension; }

	bool operator<(const CFile& cfile) {
		return cfile.file_name < file_name; }

	bool operator>(const CFile& cfile) {
		return cfile.file_extension > file_extension; }

	friend bool operator==(const CFile& cfileL,const CFile& cfileR) {
		return cfileL == cfileR; }

	CFile& operator = (const CFile& cfile) {
		file_name=cfile.file_name;
		file_extension=cfile.file_extension;
		return *this;
	}

	friend istream& operator>>(istream& os,CFile& cfile) {
		if (&os==&cin) cout<<"\nEnter name of file: ";
		os>>cfile.file_name;
		if (&os==&cin) cout<<"\nEnter an extension of file: ";
		os>>cfile.file_extension;

		return os;
	}

	friend ostream& operator<<(ostream& os,const CFile& cfile) {
		if (&os==&cout) os<<"\nName of file: ";
		os<<cfile.file_name<<' ';
		if (&os==&cout) os<<"\nExtension of file: ";
		os<<cfile.file_extension<<' ';
		
		return os;
	}

	static bool Compare_Files_By_EXN(CFile& cfileL,CFile& cfileR) {
		return cfileL.file_extension == cfileR.file_extension; 
	}

	bool operator()(CFile& arg_fileL,CFile& arg_fileR) {
		return arg_fileL.getFileName() == arg_fileR.getFileName(); 
	}
};


class CDirectory {
	string directory_Name;
	list<CFile> List_of_files;
public:
	CDirectory(const string& arg_file_name) {
		ifstream ifile(arg_file_name.c_str());
		try {
		if ( ifile.is_open()) {

			ifile >> directory_Name;

			CFile temp;

			while ( ifile >> temp) 
				List_of_files.push_back(temp);


			

		} else throw("\nError!\nCan't open file!");
		}catch(exception& e) { cout<<endl<<e.what()<<endl; }

		ifile.close();
	}

	
	
	string getDirectoryName() { return directory_Name; }

	list<CFile> getList_of_Files() { return List_of_files; }

	int get_Number_of_Files(const string& arg_name) {
		return List_of_files.size(); 
	}

	void setDirectoryName(const string& arg_d_name) { directory_Name=arg_d_name; }

	

	void Remove_Duplacate_Files() {
		List_of_files.sort();
		
		List_of_files.unique(CFile());
	}

	map<string,int> Map_of_Extension() {
		map<string,int> Result;
		int count_jpg=0,count_txt=0,count_bmp=0;
		list<CFile>::iterator iter = List_of_files.begin();
		while ( iter != List_of_files.end()) {
			if ( iter->getFileEXN() == ".jpg") count_jpg++;
			else if (iter->getFileEXN() == ".txt") count_txt++;
			else if ( iter->getFileEXN() == ".bmp") count_bmp++;
		
		++iter; 
		}
	
		Result.insert(make_pair(".jpg",count_jpg));
		Result.insert(make_pair(".txt",count_txt));
		Result.insert(make_pair(".bmp",count_bmp));
		
	
	
		return Result;

	}

	friend ostream& operator<<(ostream& os,const CDirectory cdir) {
		if (&os == &cout) os<<"\nDirectory name: ";
		os<<cdir.directory_Name<<' ';
		if (&os == &cout) os<<"\nFile info:\n";
		for (const  auto& index : cdir.List_of_files)
			os<<index<<' ';

		return os;
	}

	};



int main()
{

	const string file_name("Directory_file.txt");
	CFile file1("File1",".txt"),file2("File2",".txt"),file3("File3",".jpg"),file4("File1",".bmp"),file5("File3",".jpg"),file6("File5",".bmp");
	list<CFile>list_of_files;
	list_of_files.push_back(file1);
	list_of_files.push_back(file2);
	list_of_files.push_back(file3);
	list_of_files.push_back(file4);
	list_of_files.push_back(file5);
	list_of_files.push_back(file6);
	
	ofstream ofile(file_name.c_str());

	if (ofile.good()) {
		list<CFile>::iterator iter=list_of_files.begin();
ofile<<"Dir_Name\n";
		for (const auto& iter : list_of_files )
			ofile<<iter;

	}else throw("\nError,can't open file!\n");

	ofile.close();

	

	CDirectory obj(file_name.c_str());
	cout<<obj;
 obj.Remove_Duplacate_Files();
 cout<<"\n\nDirectory with removed identical elements: ";
 cout<<obj;

 map<string,int>Map_Result = obj.Map_of_Extension();

 cout<<"\n\nMap with extension:\n";


 for(auto index=Map_Result.begin();index!=Map_Result.end();++index) {
	 cout<<index->first<<' '<<index->second<<endl;
	
 }

	
	



	



	cout<<'\n';system("pause");return 0;
}