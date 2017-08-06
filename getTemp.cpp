/* ===================================================
C code : test.cpp
* ===================================================
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "RCSwitch.h"
#include "RcOok.h"
#include "Sensor.h"

int main(int argc, char *argv[]) {
	int RXPIN = 2;
	int TXPIN = -1;
	int loggingok = 0;   // Global var indicating logging on or off
	FILE *fp;        // Global var file handle

	char message[100];
	char buf[80];
	char filePath[1000];
    char *folderPath;
	time_t     now = time(0);
    struct tm  tstruct;


    if(argc==2) {
    	folderPath=argv[1];
    	loggingok=1;
    }

	if(wiringPiSetup() == -1)
		return 0;

	RCSwitch *rc = new RCSwitch(RXPIN,TXPIN);

	while (1) {
		if (!rc->OokAvailable()) {
			delay(1000);
			continue;
		}

		rc->getOokCode(message);
		printf("%s\n",message);

		Sensor *s = Sensor::getRightSensor(message);
		if (s == NULL) {
			delete(s);
			delay(1000);
			continue;
		}

    	now = time(0);
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%dT%XZ", &tstruct);

		printf("Date : %s\n", buf);
		printf("Temp : %f\n",s->getTemperature());
		printf("Humidity : %f\n",s->getHumidity());
		printf("Channel : %d\n",s->getChannel());

        if((!loggingok) || (s->getChannel()<=0)) {
			delete(s);
			continue;
		}

		sprintf(filePath,"%s.%02d",folderPath,s->getChannel());

		fp = fopen(filePath, "w"); // Open file where write measure
		if (fp == NULL) {
        	perror("Failed to open file!");
            exit(EXIT_FAILURE);
        }

		fprintf(fp,"Date: %s\n", buf);
		fprintf(fp,"Temp: %d\n",int(1000.0*s->getTemperature()));
		fprintf(fp,"Humidity: %d\n",int(1000.0*s->getHumidity()));
		fprintf(fp,"Channel: %d\n",s->getChannel());


        fclose(fp);

		delete s;
		return(0);
	}
}
