#include<iostream>
#include<fstream>
#include<string>

int main()
{
system("gsettings set org.gnome.shell favorite-apps \"['firefox.desktop', 'org.gnome.Nautilus.desktop']\"");
system("g++ upfav.cpp");
system("./a.out");
return 0;
}
