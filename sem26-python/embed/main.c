#include <stdio.h>
// В этом заголовочном файле собран почти весь API Python
#include <Python.h>

int main(int argc, char *argv[])
{
    Py_Initialize();
    int a;
    scanf("%d", &a);
    PyRun_SimpleString("print(a)");
    Py_Finalize();
}
