COMPILER = g++ # or CC if you prefer it on Hercules

DRIVER = tempMain

FILE = matrix

$(DRIVER) : $(FILE).o $(DRIVER).o  #the first character on the next line is a tab 
	$(COMPILER)  -o  $(DRIVER) $(FILE).o $(DRIVER).o

$(DRIVER).o :  $(DRIVER).cpp  $(FILE).cpp $(FILE).h 
	$(COMPILER) -c  $(DRIVER).cpp  -o $(DRIVER).o

$(FILE).o :  $(FILE).cpp $(FILE).h
	$(COMPILER) -c  $(FILE).cpp  -o  $(FILE).o

clean:
	@ /bin/rm -f *.o
