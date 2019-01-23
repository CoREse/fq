CC=g++
AR=ar
CPPFLAGS= -Wall -O3
LDFLAGS=
LIBS=

FQ_OBJS=fq.o
FQ_HEADERS=fq.h
EXAMPLE_OBJS=example/test.o
FQ=fq.a

libs:$(FQ)

all: $(FQ) test

$(FQ):$(FQ_OBJS)
	$(AR) -rc $@ $(FQ_OBJS)

test: $(EXAMPLE_OBJS) $(FQ)
	$(LINK.cpp) $^ -o $@

$(FQ_OBJS):$(FQ_HEADERS)

clean:
	rm *.o *.a example/*.o test
