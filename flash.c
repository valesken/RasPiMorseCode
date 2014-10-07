/* Flash an LED on GPIO 17 using /sys/class/gpio
Usage:
	Run as root (so the program can access /sys/class/gpio )
	flash <number of flashes> <milliseconds per flash>

Circuit description:
GPIO17 is on pin 11 on the J8 header of the Raspberry Pi
There is a ground at neighboring pin 9.
I put an LED and 270 ohm resistor in series between GPIO17 and ground.  
The value of the resistor in not sensitive for this, but should probably be >=100 ohms.

Jeff Kennedy, Fall 2014
*/

#include <stdlib.h>  // needed for exit
#include <unistd.h>  // needed for usleep
#include <stdio.h>
#include <ctype.h>   // for making strings all uppercase (save space)

/* A routine to open a file, write a string, and close the file */
int writeOnce(char *fname, char *data){ 
	FILE *f;
	if (f=fopen(fname,"w")){
		fprintf(f,"%s",data);
		fclose(f);
	} else {
		fprintf(stderr,"Failed to open %s\n",fname);
		exit(-1);
	}
}	 

int toMorse(char *message, FILE *fvalue)
{
  int T = (500*300); // T is 500*300 microseconds
  int i=0, j; // iterators
  int value = 0;
  int limit = 6;
  char ch;

  // some small amount of error checking (making numbers illegal)
  ch = message[i];
  while(ch != '\0')
    {
      if((int)(ch) >= 48 && (int)(ch) <= 57)
	{
	  fprintf(stderr, "Cannot convert numbers\n");
	  return 0;
	}
      ++i;
      ch = message[i];
    }
  
  // iterate through letters and use switch statement to assign appropriate times
  // note: the on-flashes are odd (e.g. j=0 -> off, j=1 -> on)
  i = 0;
  ch = message[i];
  while(ch != '\0')
    {
      for(j = 0; j < limit; ++j)
	{
	  fprintf(fvalue,"%d",value);
	  fflush(fvalue);
	  switch(toupper(ch))
	    {
	    case 'A':
	      limit = 4;
	      if(j == 3)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'B':
	      limit = 8;
	      if(j == 1)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'C':
	      limit = 8;
	      if(j == 1 || j == 5)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'D':
	      limit = 6;
	      if(j == 1)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'E':
	      limit = 2;
	      usleep(T);
	      value = value ^ 1;
	      break;
	    case 'F':
	      limit = 8;
	      if(j == 5)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'G':
	      limit = 6;
	      if(j == 1 || j == 3)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'H':
	      limit = 8;
	      usleep(T);
	      value = value ^ 1;
	      break;
	    case 'I':
	      limit = 4;
	      usleep(T);
	      value = value ^ 1;
	      break;
	    case 'J':
	      limit = 8;
	      if(j == 3 || j == 5 || j == 7)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'K':
	      limit = 6;
	      if(j == 1 || j == 5)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'L':
	      limit = 8;
	      if(j == 3)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'M':
	      limit = 4;
	      if(value == 1)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'N':
	      limit = 4;
	      if(j == 1)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'O':
	      limit = 6;
	      if(value == 1)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'P':
	      limit = 8;
	      if(j == 3 || j == 5)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'Q':
	      limit = 8;
	      if(value == 1 && j != 5)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'R':
	      limit = 6;
	      if(j == 3)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'S':
	      limit = 6;
	      usleep(T);
	      value = value ^ 1;
	      break;
	    case 'T':
	      limit = 2;
	      if(value == 1)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'U':
	      limit = 6;
	      if(j == 5)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'V':
	      limit = 8;
	      if(j == 7)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'W':
	      limit = 6;
	      if(j == 3 || j == 5)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'X':
	      limit = 8;
	      if(j == 1 || j == 7)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'Y':
	      limit = 8;
	      if(value == 1 && j != 3)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    case 'Z':
	      limit = 8;
	      if(j == 1 || j == 3)
		usleep(3*T);
	      else
		usleep(T);
	      value = value ^ 1;
	      break;
	    default:
	      break;
	    }
	}

      ++i;
      ch = message[i];
      value = 0;
      fprintf(fvalue,"%d",value);
      fflush(fvalue);
      usleep(3*T); // sleep for 3T microseconds between letters in a word
    }
  usleep(4*T); // sleep for an additional 4T (total 7T) microseconds at end of a word
  return 1;
}
	 
#define COUNT 100

int main(int argc, char *argv[]){
	FILE *fvalue;
	int i;
	char * message;
	
	/* Check that there are the right number of arguments */
	if (argc<2){
		fprintf(stderr,"Usage: %s <message to output in morse>\n",argv[0]);
		exit(-1);
	}
	
	/* Prepare GPIO */
	writeOnce("/sys/class/gpio/export","17");	        /* export GPIO17*/
	writeOnce("/sys/class/gpio/gpio17/direction","out");/* CPIO17 is to be output*/
	
	/* Open GPIO17 value "file" */
	fvalue=fopen("/sys/class/gpio/gpio17/value","w");

	/*get the parameters from the command line */
	for(i = 1; i < argc; i++)
	  {
	    message = argv[1];
	    toMorse(message, fvalue);
	  }
	
	fclose(fvalue);
	writeOnce("/sys/class/gpio/unexport","17");	      /* unexport gpio 17  */

}
