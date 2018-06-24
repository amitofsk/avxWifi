#include "./se233.h"
int main(int argc, char *argv[])
{
//example usage ./tryone.o RP2 45


//clean the file hostapd.conf
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





//Set all the config files

char command[50];
printf("Hello\n");
strcpy(command, "cp confFilesUpdated/dhcpd.conf /etc/dhcpd/dhcpd.conf");
system(command);

strcpy(command, "cp confFilesUpdated/isc-dhcp-server /etc/default/isc-dhcp-server");
system(command);

strcpy(command, "sudo ifdown wlan0");
system(command);

strcpy(command, "cp confFilesUpdated/interfaces /etc/network/interfaces");
system(command);

strcpy(command, "cp confFilesClean/hostapd.conf /etc/hostapd/hostapd.conf");
system(command);

strcpy(command, "cp confFilesUpdated/hostapd /etc/init.d/hostapd");
system(command);

//configure network address translation

strcpy(command, "cp confFilesUpdate/sysctl.conf /etc/sysctl.conf");
system(command);

strcpy(command, "sudo sh -c \"echo 1 > /proc/sys/net/ipv4/ip_forward\"");
system(command);

strcpy(command, "sudo iptables -t nat -A POSTROUTING -o wlan1 -j MASQUERADE");
system(command);

strcpy(command, "sudo iptables -A FORWARD -i wlan1 -o wlan0 -m state --state  RELATED,ENABLED -j ACCEPT");
system(command);

strcpy(command, "sudo iptables -A FORWARD -i wlan0 -o wlan1 -j ACCEPT");
system(command);

strcpy(command, "iptables-save > /etc/iptables/rules.v4");
system(command);

//First Test

return 0;
}

