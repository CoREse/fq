CC=g++
AR=ar
CPPFLAGS= -Wall -O3
LDFLAGS=
LIBS=

FQ_OBJS=fq.o
FQ_HEADERS=fq.h
EXAMPLE_OBJS=example/test.o
FQ=fq.a
DNASEQ=dnaseq/dnaseq.a

libs:$(FQ)

all: $(FQ) test

$(DNASEQ): dnaseq/*
	cd dnaseq && make

$(FQ):$(FQ_OBJS) dnaseq/dnaseq.o
	$(AR) -rc $@ $^

test: $(EXAMPLE_OBJS) $(FQ)
	$(LINK.cpp) $^ -o $@

$(FQ_OBJS):$(FQ_HEADERS)

clean:
	rm *.o *.a example/*.o test
