CC=gcc
CFLAGS=-O3 -Wall -Wextra -Wno-unknown-pragmas -Wcast-qual
LDFLAGS=
# CFLAGS=-O3 -Wall -Wextra -Wno-unknown-pragmas -Wcast-qual -g -fsanitize=thread
# LDFLAGS=-g -fsanitize=thread
# CFLAGS=-O3 -Wall -Wextra -Wno-unknown-pragmas -Wcast-qual -g -fsanitize=address
# LDFLAGS=-g -fsanitize=address
LIBS=-lm -lpthread -lz
ZOPFLI=zopfli/src/zopfli/
ZOP=deflate.o blocksplitter.o tree.o lz77.o cache.o hash.o util.o squeeze.o katajainen.o symbols.o

# use gcc and gmake on Solaris

gigz: gigz.o yarn.o try.o mySystem.o $(ZOP)
	$(CC) $(LDFLAGS) -o gigz gigz.o yarn.o try.o mySystem.o $(ZOP) $(LIBS)
	ln -f gigz ungigz

gigz.o: gigz.c yarn.h try.h mySystem.h $(ZOPFLI)deflate.h $(ZOPFLI)util.h

yarn.o: yarn.c yarn.h

try.o: try.c try.h

mySystem.o: mySystem.c mySystem.h

deflate.o: $(ZOPFLI)deflate.c $(ZOPFLI)deflate.h $(ZOPFLI)blocksplitter.h $(ZOPFLI)lz77.h $(ZOPFLI)squeeze.h $(ZOPFLI)tree.h $(ZOPFLI)zopfli.h $(ZOPFLI)cache.h $(ZOPFLI)hash.h $(ZOPFLI)util.h $(ZOPFLI)symbols.h
	$(CC) $(CFLAGS) -c $(ZOPFLI)deflate.c

blocksplitter.o: $(ZOPFLI)blocksplitter.c $(ZOPFLI)blocksplitter.h $(ZOPFLI)deflate.h $(ZOPFLI)lz77.h $(ZOPFLI)squeeze.h $(ZOPFLI)tree.h $(ZOPFLI)util.h $(ZOPFLI)zopfli.h $(ZOPFLI)cache.h $(ZOPFLI)hash.h
	$(CC) $(CFLAGS) -c $(ZOPFLI)blocksplitter.c

tree.o: $(ZOPFLI)tree.c $(ZOPFLI)tree.h $(ZOPFLI)katajainen.h $(ZOPFLI)util.h
	$(CC) $(CFLAGS) -c $(ZOPFLI)tree.c

lz77.o: $(ZOPFLI)lz77.c $(ZOPFLI)lz77.h $(ZOPFLI)util.h $(ZOPFLI)cache.h $(ZOPFLI)hash.h $(ZOPFLI)zopfli.h $(ZOPFLI)symbols.h
	$(CC) $(CFLAGS) -c $(ZOPFLI)lz77.c

cache.o: $(ZOPFLI)cache.c $(ZOPFLI)cache.h $(ZOPFLI)util.h
	$(CC) $(CFLAGS) -c $(ZOPFLI)cache.c

hash.o: $(ZOPFLI)hash.c $(ZOPFLI)hash.h $(ZOPFLI)util.h
	$(CC) $(CFLAGS) -c $(ZOPFLI)hash.c

util.o: $(ZOPFLI)util.c $(ZOPFLI)util.h
	$(CC) $(CFLAGS) -c $(ZOPFLI)util.c

squeeze.o: $(ZOPFLI)squeeze.c $(ZOPFLI)squeeze.h $(ZOPFLI)blocksplitter.h $(ZOPFLI)deflate.h $(ZOPFLI)tree.h $(ZOPFLI)util.h $(ZOPFLI)zopfli.h $(ZOPFLI)lz77.h $(ZOPFLI)cache.h $(ZOPFLI)hash.h $(ZOPFLI)symbols.h
	$(CC) $(CFLAGS) -c $(ZOPFLI)squeeze.c

katajainen.o: $(ZOPFLI)katajainen.c $(ZOPFLI)katajainen.h
	$(CC) $(CFLAGS) -c $(ZOPFLI)katajainen.c

symbols.o: $(ZOPFLI)symbols.c $(ZOPFLI)symbols.h
	$(CC) $(CFLAGS) -c $(ZOPFLI)symbols.c

dev: gigz gigzj

gigzj: gigzj.o yarn.o try.o mySystem.o
	$(CC) $(LDFLAGS) -o gigzj gigzj.o yarn.o try.o mySystem.o $(LIBS)

gigzj.o: gigz.c yarn.h try.h
	$(CC) $(CFLAGS) -DNOZOPFLI -c -o gigzj.o gigz.c

test: gigz
	./gigz -kf gigz.c ; ./gigz -t gigz.c.gz
	./gigz -kfb 32 gigz.c ; ./gigz -t gigz.c.gz
	./gigz -kfp 1 gigz.c ; ./gigz -t gigz.c.gz
	./gigz -kfz gigz.c ; ./gigz -t gigz.c.zz
	./gigz -kfK gigz.c ; ./gigz -t gigz.c.zip
	printf "" | ./gigz -cdf | wc -c | test `cat` -eq 0
	printf "x" | ./gigz -cdf | wc -c | test `cat` -eq 1
	printf "xy" | ./gigz -cdf | wc -c | test `cat` -eq 2
	printf "xyz" | ./gigz -cdf | wc -c | test `cat` -eq 3
	(printf "w" | gzip ; printf "x") | ./gigz -cdf | wc -c | test `cat` -eq 2
	(printf "w" | gzip ; printf "xy") | ./gigz -cdf | wc -c | test `cat` -eq 3
	(printf "w" | gzip ; printf "xyz") | ./gigz -cdf | wc -c | test `cat` -eq 4
	@rm -f gigz.c.gz gigz.c.zz gigz.c.zip

tests: dev test

docs: gigz.pdf

gigz.pdf: gigz.1
	groff -mandoc -f H -T ps gigz.1 | ps2pdf - gigz.pdf

all: gigz gigzj docs

clean:
	@rm -f *.o gigz ungigz gigzj gigzn gigzt gigz.c.gz gigz.c.zz gigz.c.zip gigz.pdf
