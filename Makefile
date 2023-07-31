G=g++ -std=c++17
GCC=$(G) -Wall -Wextra
LIBS=-lgtest -lgtest_main -lpthread
#SANITIZER = -fsanitize=address
SOURCES = tests.cc smartCalc2/controller/controller.cc smartCalc2/model/model.cc

all: clean tests

install: clean
	mkdir build
	cd smartCalc2 && qmake && make && make clean && rm Makefile
	cd ..
	mv smartCalc2/smartCalc2.app build
	rm smartCalc2/.qmake.stash

uninstall:
	-rm -rf build

clean:
	@-rm -rf test
	@-rm -rf test.info
	@-rm -rf *.gcda
	@-rm -rf *.gcno
	@-rm -rf report
	@-rm -rf leaks*
	@echo .................. im clean now ..................

dvi:
	open readme.md

dist:
	@-rm -rf Archive_SmartCalc_v2.0/
	@mkdir Archive_SmartCalc_v2.0/
	@mkdir Archive_SmartCalc_v2.0/src
	@mv ./build/smartCalc2.app Archive_SmartCalc_v2.0/src/
	@tar cvzf Archive_SmartCalc_v2.0.tgz Archive_SmartCalc_v2.0/
	@rm -rf Archive_SmartCalc_v2.0/
	@rm -rf build


tests: clean
	@$(GCC) $(SOURCES) -o test $(LIBS)
	@./test
	@make clean

gcov_report: clean
	$(GCC) --coverage $(SOURCES) -o test $(LIBS)
	chmod +x *
	./test
	#lcov -t "test" -o test.info --no-external -c -d .
	lcov --ignore-errors mismatch -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

leaks: clean
	@echo .................. testing for leaks ..................
	@$(GCC) $(SOURCES) -lgtest -o leaks -g
	CK_FORK=no leaks --atExit -- ./leaks
	@make clean

open:
	cd build/smartCalc2.app/Contents/MacOS && ./smartCalc2

clang_format:
	@echo ------------------ clang-format check -----------------------
	clang-format -n *.cc smartCalc2/*/*.h smartCalc2/*/*.cc
