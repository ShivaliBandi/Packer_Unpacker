// This program demonstates temorary file creation

#include<stdio.h>

int main()
{
FILE *fp;

fp = tmpfile();
printf("Temorary file is Created \n");

if(fp == NULL)
{
	printf("Unable to create temorary file.\n");
}

// Now we can use this fp for further file operation

return 0;
}
