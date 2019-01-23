#ifndef CRE_BIO_FQ
#define CRE_BIO_FQ

#include <string>

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
	char* Id, Seq, Qid, Q;
	public:
		FqEntry();
		~FqEntry();
		FqEntry(FqEntry&);//it's more like move than copy
		FqEntry& duplicate() const;//This is copy
		FqEntry& operator=(FqEntry&);
};

class fq
{

};

#endif
