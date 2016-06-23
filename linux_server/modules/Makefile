obj-m += lkm.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install:
	insmod lkm.ko

remove:
	rmmod lkm

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
