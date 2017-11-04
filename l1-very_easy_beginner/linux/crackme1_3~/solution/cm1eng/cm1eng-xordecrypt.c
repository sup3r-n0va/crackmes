#define __USE_INLINE_ASM

#include <stdio.h>
#ifndef __USE_INLINE_ASM
#include <string.h>
#endif


/*

solution for lord's Easy crackme 2

see v4mp1r3's solution for static disassembly and program analysis.
we will use that understanding to show a few different methods of 
password recovery.

we could use a debugger and set a breakpoint after the password
is decrypted at 0x80480c5 and then examine the memory at 0x8049126
to phish the decrypted password from the program.  let's have a
look:

(gdb) break *0x80480c5
Breakpoint 1 at 0x80480c5
(gdb) run
Starting program: cm1eng
warning: shared library handler failed to enable breakpoint

Password : test123

Breakpoint 1, 0x080480c5 in ?? ()

(gdb) x/s 0x8049126
0x8049126:       "pucybut"

(gdb) x/s 0x804911b
0x804911b:       "test123\n  "

it is clear which is the password we entered and which is the 
password the program expects.


or we could write a loop in c to decrypt the password, which 
is simply xor encrypted with byte 0x21.  undefine
__USE_INLINE_ASM above for that solution.


instead, let's work on some gnu inline assembly.  it should
be simple enough to write a short solution.

program output:

decrypting password "QTBXCTU"...
decrypted password is "pucybut".

*/

int main (int argc, char *argv[]) {
  char pass[]="QTBXCTU";

#ifdef __USE_INLINE_ASM
  unsigned long int p = (unsigned long int) pass;
  unsigned long int q = p;
#else
  int i;
#endif

  printf("decrypting password \"%s\"...\n", pass);

#ifdef __USE_INLINE_ASM
  __asm__("movl (%0), %1                    \n\t" \
          "xorl $0x21212121, %1             \n\t" \
          "movl %1, (%0)                    \n\t" \
          "addl $0x4, %0                    \n\t" \
          "movl (%0), %1                    \n\t" \
          "xorl $0x212121, %1               \n\t" \
          "movl %1, (%0)                    \n\t" \
          : "=a" (p), "=b" (q) : "a" (p));
#else
  for (i=0 ; i < strlen(pass) ; i++) {
    pass[i] = pass[i] ^0x21;
  }
#endif

  printf("decrypted password is \"%s\".\n", pass);

  return 0;
}
