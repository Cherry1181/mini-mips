#include<bits/stdc++.h>
using namespace std;

string get_line(int n) {
	string str;
	fstream new_file;
	new_file.open("text.txt",ios::in);
    for(int i=0;i<n;i++)
    	getline(new_file,str);
    return str;
} 
int main(int argc, char const *argv[])
{   int line_num=0;
	fstream new_file;
	new_file.open("text.txt",ios::in);
	string str;
	while(getline(new_file,str)) {
		line_num+=1;
	cout << str << endl;
	}
    str=get_line(3);
    cout << str << endl;
	return 0;
}