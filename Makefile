# build it, run it

dis_8080: dis_8080.c
	cc -o dis_8080 dis_8080.c

run:
	./dis_8080 rom.bin >rom.out
