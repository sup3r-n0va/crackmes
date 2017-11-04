#include <sys/types.h>
#include <pwd.h>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(void)
{
	const string username = getpwuid(getuid())->pw_name;
	const string keyfilename = ".key_" + username;

	cout << "Generating " << keyfilename << endl;

	ofstream keyfile(keyfilename.c_str());
	if ( !keyfile.good() )
	{
		cerr << "error: cannot open " << keyfilename << " for writing" << endl;
		return EXIT_FAILURE;
	}

	keyfile.seekp(0, ios_base::beg);

	string key = "";
	int n = 0;

	for ( int i = 0 ; i < username.size() ; ++i )
	{
		char c = username[i], d;
		int j,x,y,z;

		d = c-n;
		x = d/25; y = (d % 25)/5; z = (d % 25) % 5;

		for ( j = 0 ; j < x ; ++j ) key += "*****+-";
		for ( j = 0 ; j < y ; ++j ) key += '*';
		for ( j = 0 ; j < z ; ++j ) key += '+';

		key += ','; key += c;
	
		n = c/10;

	}

	keyfile << key.c_str();

	keyfile.close();

	cout << "Done." << endl;

	return EXIT_SUCCESS;
}
