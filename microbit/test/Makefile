
SOURCES := main.c logic.c 

OBJ := main.o logic.o 

#PHONY gjer at vi må kalle make
.PHONY : logic
logic : 
	gcc $(SOURCES) -o $@

#Vi må bruke $ til å få uttrykt verdien av variablen i makefile

.PHONY : clean 
clean: 
	rm -rf $(OBJ) logic 
	#logic viser til ka linker vi skal slette. 
