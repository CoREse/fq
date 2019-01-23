/* File: fq.cpp
 * Author: CRE
 * Last Edited: Thu Jun 21 10:11:40 2018
 */

#define LINE_BUFFER_SIZE 10000000//10M
#define BUFFER_SIZE 10000
#include <string.h>
#include <stdlib.h>
#include "fq.h"

static inline void next(const char * Id, const int Length, int &Last, int &Pos)
{
	Last=Pos+1;
	Pos=Last;
	for (;Pos<Length;++Pos)
	{
		if (Id[Pos]==':')
		{
			break;
		}
	}
}

void SeqId::resolve(const char * Id)
{
	int Last=0, Pos=0;
	int Length=strlen(Id);
	char temp[BUFFER_SIZE];
	for (;Pos<Length;++Pos)
	{
		if (Id[Pos]==':')
		{
			break;
		}
	}
	memcpy(temp,Id+Last,Pos-Last);
	temp[Pos-Last]='\0';
	instrument=temp;
	next(Id,Length,Last,Pos);
	run_number=atoi(Id+Last);
	next(Id,Length,Last,Pos);
	memcpy(temp,Id+Last,Pos-Last);
	temp[Pos-Last]='\0';
	flowcell_ID=temp;
	next(Id,Length,Last,Pos);
	lane=atoi(Id+Last);
	next(Id,Length,Last,Pos);
	tile=atoi(Id+Last);
	next(Id,Length,Last,Pos);
	x_pos=atoi(Id+Last);
	next(Id,Length,Last,Pos);
	y_pos=atoi(Id+Last);
	next(Id,Length,Last,Pos);
	read=atoi(Id+Last);
	next(Id,Length,Last,Pos);
	is_filtered=Id[Last];
	next(Id,Length,Last,Pos);
	control_number=atoi(Id+Last);
	next(Id,Length,Last,Pos);
	sample_number=atoi(Id+Last);
}
