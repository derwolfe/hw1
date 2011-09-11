#
# This code is a simple music data base illustrating the use of
# several ADTs implemented as C++ classes to decompose the problem and
# encapsulate complexity. The string268 module provides a basic string
# ADT String268, while the music_db module provides the ADTs for
# organizing a music data base.
#
KUID = 2054583 
LAB_NAME = adt

all: music_db

music_db_main.o: music_db_main.cpp string268.h music_db.h
	g++ -c -g music_db_main.cpp

string268.o: string268.cpp string268.h
	g++ -c -g string268.cpp

music_db.o: music_db.cpp music_db.h string268.h
	g++ -c -g music_db.cpp

music_db: music_db_main.o string268.o music_db.o
	g++ -g -o music_db music_db_main.o string268.o music_db.o

test1: music_db
	./music_db db_file1 db_cmd1

test2: music_db
	./music_db db_file2 db_cmd2

#################################################################

tar-file: clean
	@if test -d ../$(KUID)_$(LAB_NAME) ; then \
		( cd .. ; \
		  tar cz $(KUID)_$(LAB_NAME) >$(KUID)_$(LAB_NAME).tar.gz ; \
	  	  echo ""; \
		  echo "**************************************************************"; \
		  echo "The TAR file for you to test and hand in "; \
		  echo "   has been made in the directory above:"; \
		  echo "     " $(KUID)_$(LAB_NAME).tar.gz ; \
		  echo "**************************************************************"; \
		) ; \
	else \
		( echo "*** ERROR ** ERROR ** ERROR ** ERROR ** ERROR ** ERROR ***"; \
		  echo "The <your KUID>_<lab-name> directory was not found. "; \
		  echo "Remember that you should rename the "; \
		  echo "\"starter-code\" directory created by the "; \
		  echo "starter TAR file and set the KUID " ; \
		  echo "variable in the Makefile"; \
		) ; \
	fi


# Remember to add executables to the clean target
#
clean:
	rm -f *~ *.o music_db core.*
