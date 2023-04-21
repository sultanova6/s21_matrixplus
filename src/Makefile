CC = g++
CPPFLAGS = -lgtest -std=c++17
CHECKFLAGS = -Wall -Werror -Wextra

all: clean s21_matrix_oop.a test

test:
	@${CC} test_plus.cc s21_matrix_oop.cc ${CHECKFLAGS} ${CPPFLAGS}
	@./a.out

s21_matrix_oop.a:
	@$(CC) $(CHECKFLAGS) s21_matrix_oop.cc -c
	@ar r s21_matrix_oop.a s21_matrix_oop.o

clean:
	@/bin/rm -rf *.o *.a matrix *.gcno *gcda report *.info matrix *.out *.dSYM *.cfg

check:
	@cp ../materials/linters/.clang-format .
	@clang-format -n s21_matrix_oop.cc s21_matrix_oop.h
	@rm -rf .clang-format

git:
	git add .
	git commit -m '1'
	git push origin develop