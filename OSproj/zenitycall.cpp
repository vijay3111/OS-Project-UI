#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main ()
{
fstream f;
f.open("OSproj/applnfile", ios::in);
if (!f) 
{
	cout << "File not there!";
}

else 
{
int c=1;
int n;
fstream f2;
f2.open("OSproj/config",ios::in);
if (!f2) 
{
	cout << "Config File not there! Taking parameter as 3 by default";
	n=3;
}
else{
while(!f2.eof())
{
	string s;
	getline(f2,s);
	if(s.substr(0,15)=="set_notif_count")
	{
		string num=s.substr(16);
		n=stoi(num);
		break;
	}
}
}

string commandstr="zenity --error --title \"Notification\" --text \"The following are the high memory consuming applications:\\n";
string arr[n];
int k=0;
while(c<=n)
	{
	string str;
	getline(f,str);
	int sc=0;
	string s=""; bool f=false;
	if(str.substr(0,4)=="/usr")
	{
	cout<<str<<'\n';
	for(int i=0;i<str.length();i++)
	{
		if(sc==4)
			break;
		else if(sc==3&&str[i]!='/')
		{
			s+=str[i];
			f=true;
		}
		if(str[i]=='/')
			sc++;
	}
	}
	if(str[0]!='/' && str!="CMD")
	{
		f=true;
		s=str;
	}
	for(int i=0;i<k;i++)	
		if(arr[i]==s)
			f=false;

	//cout<<s<<'\n';
	if(f)
	{
	arr[k++]=s;
	commandstr+=s;
	commandstr+="\\n";
	//cout << "\nAdded successfully\n";
	c++;
	}
	}
	commandstr+="\\n\\nYour current favorites candidate list:\\n";
	fstream f1;
	f1.open("OSproj/folderfile",ios::in);
	c=1;
	while(c<=n)
	{
	string str;
	getline(f1,str);
	string s="";
	for(auto i:str)
	{
	cout<<i<<'\n';
		if(i!='.')
			s+=i;
		else
			break;
	}
	cout<<s<<'\n';
	commandstr+=s;
	commandstr+="\\n";
	c++;
	}
	commandstr+="\"";
	commandstr+=" --width=400 --height=300 --display=:0.0";
	cout<<commandstr<<'\n';
	const char* command=commandstr.c_str();
	system(command);
	f.close();
}
	return 0;
}
