#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdint.h>

static PyObject*
dot(PyObject *self, PyObject *args);

PyObject*
PyInit_matrix();

static PyObject*
create_module();

int
main() {
    PyImport_AppendInittab("matrix", create_module);
    
    Py_Initialize();
}

static PyObject*
create_module() {
    PyErr_SetString(PyExc_RuntimeError, "Not implemented yet");
    return NULL;
}

static PyObject*
dot(PyObject *self, PyObject *args) {
    int32_t matrix_size;
    PyObject* A;
    PyObject* B;
    if (!PyArg_ParseTuple(args, "i|O|O", &matrix_size, &A, &B)) {
        // not valid arguments
    }
    PyObject* result = PyList_New(0);
    for (int32_t i = 0; i < matrix_size; ++i) {
        PyObject* current_line = PyList_New(0);
        for (int32_t j = 0; j < matrix_size; ++j) {
            int64_t current_result = 0;
            for (int32_t k = 0; k < matrix_size; ++k){
                int64_t element_from_A = 0;
                if (i < PyList_Size(A) && k < PyList_Size(A))
                    element_from_A = PyLong_AsLong(PyList_GetItem(PyList_GetItem(A, i), k));
                int64_t element_from_B = 0;
                if (j < PyList_Size(B) && k < PyList_Size(B))
                    element_from_B = PyLong_AsLong(PyList_GetItem(PyList_GetItem(B, k), j));
                current_result += element_from_A * element_from_B;
            }
            PyList_Append(current_line, PyLong_FromLong(current_result));
        }
        PyList_Append(result, current_line);
    }
    return result;
}

PyObject* PyInit_matrix(void) {
    
    static PyMethodDef methods[] = {
     {
        // name of the method
        .ml_name = "dot",
        // pointer
        .ml_meth = dot,
        // flags for using C
        .ml_flags = METH_VARARGS,
        // description
        .ml_doc = "Do something very useful"
     },
        // end
        {NULL, NULL, 0, NULL}
    };
    
    static PyModuleDef moduleDef = {
        .m_base = PyModuleDef_HEAD_INIT,
        // module name
        .m_name = "matrix",
        // additional memory
        .m_size = -1,
        // methods
        .m_methods = methods,
    };
    return PyModule_Create(&moduleDef);
}
