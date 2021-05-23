msg=Default message

CC = g++
CCFLAGS = -c -Wall -std=c++14
LDFLAGS = -lm

# add your .cpp files here  (no file suffixes)
CLASSES = ex2

# Prepare object and source file list using pattern substitution func.
OBJS = $(patsubst %, %.o,  $(CLASSES))
SRCS = $(patsubst %, %.c, $(CLASSES))

all: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o find_the_author

%.o: %.c
	$(CC) $(CCFLAGS) $*.c

depend:
	makedepend -- $(CCFLAGS) -- $(SRCS)
# DO NOT DELETE
push:
	git add -A
	git commit -m "$(msg)"
	git push

tar:
	tar -cvf ex2.tar ex2.cpp FileVector.cpp FileVector.h Makefile

tests:
	./find_the_author frequent_words.txt unknown.txt hamilton.txt hamlet.txt ladygaga.txt short.txt > Outputs/myOut.txt
	./school_sol frequent_words.txt unknown.txt hamilton.txt hamlet.txt ladygaga.txt short.txt > Outputs/schoolOut.txt
	diff Outputs/myOut.txt Outputs/schoolOut.txt
	./find_the_author frequent_words.txt texts/unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/myOut.txt
	./school_sol frequent_words.txt texts/unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/schoolOut.txt
	diff Outputs/myOut.txt Outputs/schoolOut.txt
	./find_the_author texts/frequent_words.txt texts/unknown.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt hamilton.txt > Outputs/myOut.txt
	./school_sol texts/frequent_words.txt texts/unknown.txt  texts/hamlet.txt texts/ladygaga.txt texts/short.txt hamilton.txt > Outputs/schoolOut.txt
	diff Outputs/myOut.txt Outputs/schoolOut.txt
	./find_the_author texts/frequent_words.txt unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/myOut.txt
	./school_sol texts/frequent_words.txt unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/schoolOut.txt
	diff Outputs/myOut.txt Outputs/schoolOut.txt
	./find_the_author texts/frequent_words.txt texts/unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/myOut.txt
	./school_sol texts/frequent_words.txt texts/unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/schoolOut.txt
	diff Outputs/myOut.txt Outputs/schoolOut.txt

nothing_opens_test:
	./find_the_author frequent_words.txt unknown.txt hamilton.txt hamlet.txt ladygaga.txt short.txt > Outputs/myOut.txt
	./school_sol frequent_words.txt unknown.txt hamilton.txt hamlet.txt ladygaga.txt short.txt > Outputs/schoolOut.txt
	tkdiff Outputs/myOut.txt Outputs/schoolOut.txt
no_freq_test:
	./find_the_author frequent_words.txt texts/unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/myOut.txt
	./school_sol frequent_words.txt texts/unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/schoolOut.txt
	tkdiff Outputs/myOut.txt Outputs/schoolOut.txt
no_others_test:
	./find_the_author texts/frequent_words.txt texts/unknown.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt hamilton.txt > Outputs/myOut.txt
	./school_sol texts/frequent_words.txt texts/unknown.txt  texts/hamlet.txt texts/ladygaga.txt texts/short.txt hamilton.txt > Outputs/schoolOut.txt
	tkdiff Outputs/myOut.txt Outputs/schoolOut.txt
no_unknown_test:
	./find_the_author texts/frequent_words.txt unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/myOut.txt
	./school_sol texts/frequent_words.txt unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/schoolOut.txt
	tkdiff Outputs/myOut.txt Outputs/schoolOut.txt
test:
	./find_the_author texts/frequent_words.txt texts/unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/myOut.txt
	./school_sol texts/frequent_words.txt texts/unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt > Outputs/schoolOut.txt
	tkdiff Outputs/myOut.txt Outputs/schoolOut.txt
school_test:
	./school_sol texts/frequent_words.txt texts/unknown.txt texts/hamilton.txt texts/hamlet.txt texts/ladygaga.txt texts/short.txt
	./school_sol simple_test/freq_words.txt simple_test/unknown.txt simple_test/sample1.txt simple_test/sample2.txt
