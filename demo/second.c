// Program which demonstate use of and change of current working directory.
// Every process has a current working directory. This directory is where the search 
// for all relative pathnames starts (Relative path names).

#include<fcntl.h>
#include<stdio.h>

int main()
{
	int return_value;
	int fd;
	char name[100] = {'\0'};


	// We can change the current working directory of the calling process by 
	// calling the chdir or fchdir functions.

	return_value = getcwd(name,sizeof(name));
	printf("\nCurrent working directory before change is : %s\n\n",name);

	return_value = chdir("NewDirectory");
	if(return_value == -1)
	{
		printf("Unable to change current working directory\n");
		return -1;
	}
	printf("Current working directory is succefully changed...\n");

	// In this case file is searched from NewDirectory
	fd = open("file.txt",O_RDONLY);
	if(fd == -1)
	{
		printf("Unable to open file");
		return -1;
	}
	printf("File gets successfully opened after changing current working directory..\n");

	// We can check our current working directory by calling getcwd()
	// The getcwd() function copies an absolute pathname of the current working directory to the array pointed 		//to by buf, which is of length size.

	return_value = getcwd(name,sizeof(name));

	if(return_value == -1)
	{
		printf("Unable to get current working directory\n");
		return -1;
	}

	printf("\nCurrent working directory is : %s\n\n",name);
	return 0;
}
