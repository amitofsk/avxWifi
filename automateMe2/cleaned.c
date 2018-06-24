#include "se233.h"
int main(int argc, char *argv[])
{
char newName[20];
int length=24;
int i;
FILE * infile;
FILE * outfile;
char buf[100];
infile=fopen("confFilesOrig/hostapd.conf","r");
outfile=fopen("confFilesClean/hostapd.conf","w");
for(i=0;i<24;i++)
{
   fgets(buf,100,infile);
   if(i==3)
     {
      //change the name from Pi_AP to something else
      strcpy(newName, "ssid=");
      strcat(newName,argv[1]);
      strcat(newName, "\n");
      strcpy(buf, newName);
     }     
   fputs(buf, outfile); 
}


fclose(infile);
fclose(outfile);
return 0;
}
