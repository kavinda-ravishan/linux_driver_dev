obj-m += ldd.o

all: sls_dev app

sls_dev: ldd.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

app: app.cpp
	g++ -std=c++17 -c -o app.o app.cpp
	g++ -std=c++17 -o app.out app.o

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f *.o *.out
