#ifndef CRE_BIO_FQ
#define CRE_BIO_FQ

#include <string>
#include <stdio.h>
#include "dnaseq/dnaseq.h"

class SeqId
{
	public:
	std::string instrument;
	int run_number;
	std::string flowcell_ID;
	int lane,tile,x_pos,y_pos,read;
	char is_filtered;
	int control_number, sample_number;
	SeqId();
	void resolve(const char *);
};

class FqEntry
{
	FILE* ReadFile;
	void allocate();
	public:
		char* Id, *Qid, *Q;
		DNASeq Seq;
		FqEntry(const char * FileName=NULL);
		~FqEntry();
		//FqEntry(FqEntry&);//it's more like move than copy
		FqEntry& copy(const FqEntry&);//This is copy, will not copy the ReadFile
		//FqEntry& operator=(FqEntry&);
		void close();
		void open(const char * FileName);
		bool readNext();//return true if success
	private:
		FqEntry(const FqEntry&);
		FqEntry & operator=(const FqEntry&);
};

class fq
{

};

unsigned int fieldify(char * Fields, const char **Result, char Separate=':');

#endif
