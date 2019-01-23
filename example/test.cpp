#include "../fq.h"
#include <stdio.h>

int main (int argc, char **argv)
{
    if (argc!=2)
    {
        fprintf(stderr,"test FqFileName\nRead the fq file and print it to stdout.\n");
        return 1;
    }
    FqEntry Read(argv[1]);
    bool First=true;
    while (Read.readNext())
    {
        if (!First) printf("\n");
        First=false;
        printf("%s\n%s\n%s\n%s",Read.Id,Read.Seq,Read.Qid,Read.Q);
    }
    return 0;
}