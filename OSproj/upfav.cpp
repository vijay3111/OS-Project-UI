#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main ()
{
fstream f;
f.open("folderfile", ios::in);
if (!f) {
cout << "Folder File not there!";
}
else 
{
int c=1;
int n;
fstream f2;
f2.open("config",ios::in);
if (!f2) {
cout << "Config File not there! Taking parameter as 2 by default";
n=2;
}
while(!f2.eof())
{
string s;
getline(f2,s);
//cout<<s.substr(0,14)<<'\n';
if(s.substr(0,14)=="set_favs_count")
{
string num=s.substr(15);
n=stoi(num);
cout<<n<<'\n';
break;
}
}

while(c<=n)
	{
	string str;
	getline(f,str);
string commandstr="gsettings set org.gnome.shell favorite-apps \"$(gsettings get org.gnome.shell favorite-apps | sed s/.$//),'";
	commandstr+=str;
	commandstr+="']\"";
	cout<<commandstr<<'\n';
	const char* command=commandstr.c_str();
	system(command);
	cout << "\nAdded successfully\n";
	c++;
	}
f.close();
}
	return 0;
}
