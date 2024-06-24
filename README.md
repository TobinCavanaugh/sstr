## sstr.h
### A stack based dynamic string allocation library

#### Why use `sstr.h`?
1. No more manual freeing and allocating of temporary working strings.
2. No worry about buffer overflows in the case of doing fixed size buffers with libC string functions.
3. Macro based for no additional function calls.
4. Significantly faster than stack allocation, without the chance for memory leaks.

Hello World Example:
```C
$ a = $from("Hello");
a = $append(a, " World!");
printf("%s\n", a);
```
`>Hello World!`

Loop Example:
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
