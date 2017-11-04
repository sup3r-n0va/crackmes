// keygen for browselagalopex's cm1
// http://www.crackmes.de/users/lagalopex/cm1/

// Compile with
// $ gcc -Wall -Wextra -Werror -pedantic -ansi -std=c99 -O3 keygen.c
// No flag is requisite.

// The key depends on the current user name. The idea is that the key is
// a sequence of strings of the form XXXX,Y where Y is a letter of the
// user name and XXXX a combination of characters of "+*-/".
// Consider a counter ESI initialized to zero. When ",Y" is reached, ESI
// must have the ASCII value of Y. In XXXX, you can change ESI with:
//   * +: adds 1 to ESI;
//   * *: adds 5 to ESI;
//   * -: substractes 1 to ESI;
//   * /: substractes 5 to ESI;
// You cannot have more than five times a sequence of the same character
// repeated once (e.g. "++") in XXXX.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main()
{
	struct passwd* pwd = getpwuid(getuid());
	fprintf(stderr, "Redirect stdout to ~/.key_%s\n", pwd->pw_name);
	char* c = pwd->pw_name;
	int esi = 0;
	while (*c)
	{
		int t = *c - esi;
		while (t)
		{
			if (t >= 5)
			{
				t -= 5;
				printf("*");
			}
			if (t)
			{
				t--;
				printf("+");
			}
		}
		printf(",%c", *c);
		esi = *c / 10;
		c++;
	}
	return 0;
}
