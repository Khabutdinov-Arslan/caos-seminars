#include <stdio.h>
#include <Python.h>

int main(int argc, char *argv[])
{
    int a;
    scanf("%d", &a);
    char buff[50];
    sprintf(buff, "a=%d\nprint(a ** 2)", a);
    Py_Initialize();
    PyRun_SimpleString(buff);
    Py_Finalize();
}
