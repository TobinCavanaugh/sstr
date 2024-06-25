# sstr.h 

### A stack based dynamic string allocation library

#### Why use `sstr.h`?
1. No more manual freeing and allocating of temporary working strings.
2. No worry about buffer overflows in the case of doing fixed size buffers with libC string functions.
3. Macro based for no additional function calls.
4. Significantly faster than stack allocation, without the chance for memory leaks.

#### Hello World Example:
```C
$ a = $from("Hello");
a = $append(a, " World!");
printf("%s\n", a);
```
`>Hello World!`

#### Loop Example:
> We use the $begin(NAME) and $end(NAME) in order to create a stack frame as scoped blocks don't 'free' stack allocated memory. This functionality relies on GCCs nested function extension.
```C
int i = 10000;
for (; i >= 0; i--) {
  $begin(a)
    $ a = $from_fmt("%d", i);
    printf("%s\n", a);
  $end(a)
}
```
`>10000`
`>9999`
`...`

#### Complex Functionality Example:
> This demonstrates the stack allocated nature and the speed of the operations we perform. Note the fact that there is no use of the `free` keyword, however the `i` value can be arbitrarily high without any concern of freeing. There is also no concern over buffer overruns, as all functions are designed to gracefully handle out of bounds indexing.
```C
#include <stdio.h>
#include "sstr.h"

void PrintThing(int x, float y, $ z) {
    $ str = $from_fmt("%d, %f, %s", x, y, z);

    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    //Get the timestamp
    $ working = $from_fmt("%s", asctime(timeinfo));

    //Remove newline at the end
    working[strlen(working) - 1] = '\0';

    //Append our values string
    working = $append(working, str);

    //Insert a pipe character between the two strings
    working = $insert(working, strlen(working), " | ");

    printf("%s", working);
}

int main() {
    int i = 1000000;
    for (; i >= 0; i--) {
        PrintThing(100, .5f, "String");
    }
}

```


## sstr.h
<img width=200em src="https://github.com/TobinCavanaugh/sstr/blob/master/logo/logo.png?raw=true"/>