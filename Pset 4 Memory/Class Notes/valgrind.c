// Buggy program

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x = malloc(sizeof(int)*3); // We can see the return value as an array

    // I will make a mistake starting from 1 and causing a buffer overflow
    x[1] = 72;  // H
    x[2] = 73;  // I
    x[3] = 33;  // !  Buffer overflow, maybe SEGFAULT ==4101== Invalid write of size 4

    // ==4101== 12 bytes in 1 blocks are definitely lost in loss record 1 of 1
    // free(x);
}

/*

####    valgrind ./valgrind    #####

    2 errors generated.
    make: *** [<builtin>: valgrynd] Error 1
    Pset 4: Memory/Class Notes/ $ make valgrynd
    Pset 4: Memory/Class Notes/ $ valgrynd ./valgrynd
    bash: valgrynd: command not found
    Pset 4: Memory/Class Notes/ $ make valgrind
    Pset 4: Memory/Class Notes/ $ valgrind ./valgrind
    ==4101== Memcheck, a memory error detector
    ==4101== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==4101== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
    ==4101== Command: ./valgrind
    ==4101==
    ==4101== Invalid write of size 4
    ==4101==    at 0x109170: main (valgrind.c:13)
    ==4101==  Address 0x4bb504c is 0 bytes after a block of size 12 alloc'd
    ==4101==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==4101==    by 0x109151: main (valgrind.c:8)
    ==4101==
    ==4101==
    ==4101== HEAP SUMMARY:
    ==4101==     in use at exit: 12 bytes in 1 blocks
    ==4101==   total heap usage: 1 allocs, 0 frees, 12 bytes allocated
    ==4101==
    ==4101== 12 bytes in 1 blocks are definitely lost in loss record 1 of 1
    ==4101==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==4101==    by 0x109151: main (valgrind.c:8)
    ==4101==
    ==4101== LEAK SUMMARY:
    ==4101==    definitely lost: 12 bytes in 1 blocks
    ==4101==    indirectly lost: 0 bytes in 0 blocks
    ==4101==      possibly lost: 0 bytes in 0 blocks
    ==4101==    still reachable: 0 bytes in 0 blocks
    ==4101==         suppressed: 0 bytes in 0 blocks
    ==4101==
    ==4101== For lists of detected and suppressed errors, rerun with: -s
    ==4101== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

*/