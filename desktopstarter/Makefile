DEBUG ?= -DNODEBUG

build: desktopstarter

desktopstarter: *.c BarnabasBox/libbarnabas.a
	$(CC) -o desktopstarter *.c BarnabasBox/libbarnabas.a

BarnabasBox/libbarnabas.a:
	make -C BarnabasBox build

clean:
	rm -f desktopstarter
	make -C BarnabasBox clean
