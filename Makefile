COMPILER := g++
CVERSION := -std=c++20
CFLAGS := -O2
EXECUTABLENAME := runner
SRC := ./src/*.cpp 
INC := ./include*.cpp

standard:
	$(COMPILER) -DTIMETEST -DGENTEST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe gen_array_time.csv
	$(COMPILER) $(CFLAGS) -DTIMETEST -DADDTEST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe add_array_time.csv
	$(COMPILER) $(CFLAGS) -DTIMETEST -DMULTTEST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe mul_array_time.csv
	$(COMPILER) $(CFLAGS) -DTIMETEST -DPROCTEST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe pro_array_time.csv

	$(COMPILER) -DMEMORYTEST -DGENTEST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe gen_array_mem.csv
	$(COMPILER) $(CFLAGS) -DMEMORYTEST -DADDTEST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe add_array_mem.csv
	$(COMPILER) $(CFLAGS) -DMEMORYTEST -DMULTTEST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe mul_array_mem.csv
	$(COMPILER) $(CFLAGS) -DMEMORYTEST -DPROCTEST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe pro_array_mem.csv


	$(COMPILER) -DTIMETEST -DGENTEST -DLIST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe gen_list_time.csv
	$(COMPILER) $(CFLAGS) -DTIMETEST -DADDTEST -DLIST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe add_list_time.csv
	$(COMPILER) $(CFLAGS) -DTIMETEST -DMULTTEST -DLIST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe mul_list_time.csv
	$(COMPILER) $(CFLAGS) -DTIMETEST -DPROCTEST -DLIST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe pro_list_time.csv

	$(COMPILER) -DMEMORYTEST -DGENTEST -DLIST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe gen_list_mem.csv
	$(COMPILER) $(CFLAGS) -DMEMORYTEST -DADDTEST -DLIST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe add_list_mem.csv
	$(COMPILER) $(CFLAGS) -DMEMORYTEST -DMULTTEST -DLIST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe mul_list_mem.csv
	$(COMPILER) $(CFLAGS) -DMEMORYTEST -DPROCTEST -DLIST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe pro_list_mem.csv

test:
	$(COMPILER) $(CFLAGS) -DTEST -DLIST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe
	$(COMPILER) $(CFLAGS) -DTEST $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)
	./runner.exe