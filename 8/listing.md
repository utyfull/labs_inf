```
utyfull@ubuntuWork:~/Desktop/labs/8$ emacs helloworld.c
utyfull@ubuntuWork:~/Desktop/labs/8$ ls
helloworld.c  MakeFile.o
utyfull@ubuntuWork:~/Desktop/labs/8$ cat helloworld.c
#include <stdio.h>

int main(){
  printf("Hello, Charles!\n");
  return 0;
}
utyfull@ubuntuWork:~/Desktop/labs/8$ emacs MakeFile.o
utyfull@ubuntuWork:~/Desktop/labs/8$ ls
helloworld.c  MakeFile.o  MakeFile.o~
utyfull@ubuntuWork:~/Desktop/labs/8$ cat MakeFile.o
all:
	gcc ./helloworld.c
	./a.out
	rm a.out
utyfull@ubuntuWork:~/Desktop/labs/8$ make -f MakeFile.o
gcc ./helloworld.c
./a.out
Hello, Charles!
rm a.out
utyfull@ubuntuWork:~/Desktop/labs/8$ ls
helloworld.c  MakeFile.o  MakeFile.o~
```

