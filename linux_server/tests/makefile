INCLUDE=../serv/include
SRC=../serv/src
BUILD=../serv/build

all: server libstub test run report

server:
	make -C $(BUILD) cov

libstub:
	$(CC) -I$(INCLUDE) -fPIC $(SRC)/os.c -shared -o libstub.so

test:
	$(CXX) -g -I$(INCLUDE) os_mock.cpp server_test.cpp \
	$(SRC)/s_prep.o \
	$(SRC)/server.o \
	$(SRC)/reactor.o \
	$(SRC)/protocol.o \
	$(SRC)/s_config.o \
	$(SRC)/acceptor.o \
	$(SRC)/client_handler.o \
	$(SRC)/s_echos.o \
	$(SRC)/interface.o \
	-L. -Wl,--no-as-needed -ldl -lstub -lconfig -lgtest -lgmock -lgmock_main -lpthread -lgcov -o server_test


run:
	./run.sh

report:
	mkdir html
	lcov --capture --directory $(SRC) --output-file cov.info
	genhtml cov.info --output-directory html

clean:
	make -C $(BUILD) clean
	rm -f $(SRC)/*.gcda
	rm -f $(SRC)/*.gcno
	rm -f libstub.so server_test cov.info
	rm -rf html


