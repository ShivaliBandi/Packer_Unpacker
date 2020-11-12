//combine data of all files using structure as filename and file size as a seperator
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<ctype.h>
#include<string.h>
#include<dirent.h>
#include <sys/stat.h>
#include<stdlib.h>

struct FileDet
{
    char fname[100];
    int fsize;
}filename;

int packer(char *directoryName)
{
     struct dirent *de;  
    DIR *dr = opendir(directoryName);
    struct stat stats;
    int iresult=0;
    char buffer[1000]={'\0'};
    int fddest=creat("output.txt",0777);
    int fdsrc;
    int wfd;
    char path[1000]={'\0'};
    char line[]="\n---------------------------------------------------------------------------------\n";
    if((stat(directoryName, &stats)!=-1) &&(S_ISDIR(stats.st_mode)!=0) )
    {
       
            if (dr == NULL)  
                return -1;//unable to open directory
            while (((de = readdir(dr)) != NULL) )
            {
                if(de->d_type==8)
                {
                    sprintf(path,"%s/%s",directoryName,de->d_name);
                    stat(path,&stats);
                    strcpy(filename.fname,de->d_name);
                    filename.fsize=stats.st_size;
                    write(fddest,&filename,sizeof(filename));
                    memset(&filename,0,sizeof(filename));


                    fdsrc=open(path,O_RDONLY);
                    while((wfd=read(fdsrc,&buffer,sizeof(buffer)))!=0)
                    {
                        write(fddest,buffer,wfd);
                    }
                    memset(buffer,0,sizeof(buffer));
                    close(fdsrc);
                    unlink(path); 
                    //printf("FILES PACKED SUCCESSFULLY\n");   

                }
                

            }
            
       closedir(dr);
    close(fddest);  
    return 1;//success
    }
    else
        return -2;//directory doesn't exist 
   
     
   
}


int unpacker(char *directoryName,char *outputFile)
{
int ret = 0;
    int fddest = 0, fdsrc = 0;
    char name[300] = {'\0'};
    struct FileDet fobj;
    char *Buffer;
    char path[1024]={'\0'};
   
    
    fdsrc = open(outputFile,O_RDONLY);
    if(fdsrc == -1)
        return -1;//unable to open packed file
    while((ret = read(fdsrc,&fobj,sizeof(fobj))) != 0)
    {
        printf("File Name : %s Size : %d\n",fobj.fname, fobj.fsize);
        sprintf(path,"%s/%s",directoryName,fobj.fname);
        fddest = creat(path,0777);
        if(fddest == -1)
            return -2;//unable to create file for unpacking
        // Dynamic memory for data to read
        Buffer = (char*)malloc(fobj.fsize);
        // Read the data from merged file
        read(fdsrc,Buffer,fobj.fsize);
        // Write the data into the newly created file
        write(fddest,Buffer,fobj.fsize);
        // Free the memory
        free(Buffer);
        close(fddest);
    }

    close(fdsrc);
    return 1;//success
}
int main()
{
    int ioptions=0,iresult=0;
    char directorName[100]={'\0'},outputFile[100]={'\0'};
    while(1)
    {
        printf("Choose Any Operation from given list\n1.Pack files\n2.Unpack Files\n");
        scanf("%d",&ioptions);
        switch (ioptions)
        {
        case 1:
            printf("Enter directory Name You want To pack\n");
            scanf("%s",directorName);
            iresult=packer(directorName);
            if(iresult==1)
                printf("FILES PACKED SUCCESSFULLY\n");
            else if(iresult==-1)
                printf("ERROR:Directory exist but unable to open directory\n");
            else if(iresult==-2)
                printf("ERROR:Directory doesn't exist\n");
            break;
        case 2:
            printf("Enter directory Name You want To pack file into that Directory\n");
            scanf("%s",directorName);
            printf("Enter file Name from which you want to unpack data\n");
            scanf("%s",outputFile);
            iresult=unpacker(directorName,outputFile);
            if(iresult==1)
                printf("FILES UNPACKED SUCCESSFULLY\n");
            else if(iresult==-1)
                printf("ERROR:Packed File For unpacking exist but unable to open file\n");
            else if(iresult==-2)
                printf("ERROR:Unable to create unpacking file\n");
            break;
        default:
            exit(0);
            break;
         }

    }   
}