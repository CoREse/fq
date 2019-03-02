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
FqEntry::FqEntry(const char * FileName)
:ReadFile(NULL),Id(NULL),Seq(LINE_BUFFER_SIZE),Qid(NULL),Q(NULL)
{
	if (FileName!=NULL)
	{
		ReadFile=fopen(FileName,"r");
		if (ReadFile==NULL) fprintf(stderr,"Open read file %s failed!",FileName);
	}
	Id=(char *)malloc(LINE_BUFFER_SIZE);
	Qid=(char *)malloc(LINE_BUFFER_SIZE);
	Q=(char *)malloc(LINE_BUFFER_SIZE);
}

FqEntry::~FqEntry()
{
	if (ReadFile!=NULL) fclose(ReadFile);
	if (Id!=NULL) free(Id);
	if (Qid!=NULL) free(Qid);
	if (Q!=NULL) free(Q);
}

/*
FqEntry& FqEntry::operator=(FqEntry& B)
{
	Id=B.Id;
	Seq.move(B.Seq);
	Qid=B.Qid;
	Q=B.Q;
	ReadFile=B.ReadFile;
	B.Id=NULL;
	B.Qid=NULL;
	B.Q=NULL;
	B.ReadFile=NULL;
	return *this;
}

FqEntry::FqEntry(FqEntry& B)
{
	*this=B;
}
*/

FqEntry& FqEntry::copy(const FqEntry& B)
{
	allocate();
	strcpy(Id,B.Id);
	Seq=B.Seq;
	strcpy(Qid,B.Qid);
	strcpy(Q,B.Q);
	return *this;
}

void FqEntry::allocate()
{
	if (Id==NULL)
	Id=(char *)malloc(LINE_BUFFER_SIZE);
	if (Qid==NULL)
	Qid=(char *)malloc(LINE_BUFFER_SIZE);
	if (Q==NULL)
	Q=(char *)malloc(LINE_BUFFER_SIZE);	
}

void FqEntry::close()
{
	if (ReadFile!=NULL)
	{
		if (0==fclose(ReadFile)) ReadFile=NULL;
		else fprintf(stderr, "Close fastQ file failed!");
	}	
}

void FqEntry::open(const char *FileName)
{
	close();
	if (ReadFile!=NULL)
	{
		fprintf(stderr, "Can't open new read file since can't close the old read file.");
		return;
	}
	ReadFile=fopen(FileName,"r");
	if (ReadFile == NULL)
		fprintf(stderr, "Open read file %s failed!", FileName);
}

bool FqEntry::readNext()
{
	if (ReadFile==NULL)
	{
		fprintf(stderr, "Can't read next entry since no ReadFile opened!");
		return false;
	}
	if (feof(ReadFile)) return false;
	unsigned L=0;
	if (fgets(Id,LINE_BUFFER_SIZE,ReadFile)==NULL) return false;
	L=strlen(Id)-1;
	if (Id[L]=='\n') Id[L]='\0';
	else if (feof(ReadFile)!=true)
	{
		fprintf(stderr, "Line too long!");
		throw -100;
	}
	if (fgets(Seq.seq,LINE_BUFFER_SIZE,ReadFile)==NULL) return false;
	L=strlen(Seq.seq)-1;
	if (Seq.seq[L]=='\n') Seq.seq[L]='\0';
	else if (feof(ReadFile)!=true) 
	{
		fprintf(stderr, "Line too long!");
		throw -100;
	}
	if (fgets(Qid,LINE_BUFFER_SIZE,ReadFile)==NULL) return false;
	L=strlen(Qid)-1;
	if (Qid[L]=='\n') Qid[L]='\0';
	else if (feof(ReadFile)!=true)
	{
		fprintf(stderr, "Line too long!");
		throw -100;
	}
	if (fgets(Q,LINE_BUFFER_SIZE,ReadFile)==NULL) return false;
	L=strlen(Q)-1;
	if (Q[L]=='\n') Q[L]='\0';
	else if (feof(ReadFile)!=true)
	{
		fprintf(stderr, "Line too long!");
		throw -100;
	}
	return true;
}