
DIRECTORIOS := $(shell find . -maxdepth 1 -name "boost*" -type d)

all: 
	for dir in $(DIRECTORIOS); do make -C $$dir; done

clean:
	for dir in $(DIRECTORIOS); do make -C $$dir clean; done
