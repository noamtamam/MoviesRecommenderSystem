CC=g++
CXXFLAGS= -Wall -Wvla -Wextra -Werror -g -std=c++14
LDFLAGS= -lm
HEADERS= Movie.h RecommenderSystem.h RecommenderSystemLoader.h RSUser.h RSUsersLoader.h
OBJS= Movie.o RecommenderSystem.o RecommenderSystemLoader.o RSUser.o RSUsersLoader.o
OBJS_TEST= tests.o

%.o : %.c

test: $(OBJS_TEST) $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	./test

out: Movie.cpp RecommenderSystem.cpp RecommenderSystemLoader.cpp RSUser.cpp RSUsersLoader.cpp
	CC Movie.cpp RecommenderSystem.cpp RecommenderSystemLoader.cpp RSUser.cpp RSUsersLoader.cpp print_main.cpp -o out

$(OBJS) : $(HEADERS)
$(OBJS_TEST) : tests.cpp

.PHONY: clean_test

clean_test:
	rm -rf *.o
	rm -rf test




