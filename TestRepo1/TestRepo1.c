#include <Python.h>

/*
 * Implements an example function.
 */
PyDoc_STRVAR(TestRepo1_example_doc, "example(obj, number)\
\
Example function");

PyObject *TestRepo1_example(PyObject *self, PyObject *args, PyObject *kwargs) {
    /* Shared references that do not need Py_DECREF before returning. */
    PyObject *obj = NULL;
    int number = 0;

    /* Parse positional and keyword arguments */
    static char* keywords[] = { "obj", "number", NULL };
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi", keywords, &obj, &number)) {
        return NULL;
    }

    /* Function implementation starts here */

    if (number < 0) {
        PyErr_SetObject(PyExc_ValueError, obj);
        return NULL;    /* return NULL indicates error */
    }

    Py_RETURN_NONE;
}

/*
 * List of functions to add to TestRepo1 in exec_TestRepo1().
 */
static PyMethodDef TestRepo1_functions[] = {
    { "example", (PyCFunction)TestRepo1_example, METH_VARARGS | METH_KEYWORDS, TestRepo1_example_doc },
    { NULL, NULL, 0, NULL } /* marks end of array */
};

/*
 * Initialize TestRepo1. May be called multiple times, so avoid
 * using static state.
 */
int exec_TestRepo1(PyObject *module) {
    PyModule_AddFunctions(module, TestRepo1_functions);

    PyModule_AddStringConstant(module, "__author__", "TMotto");
    PyModule_AddStringConstant(module, "__version__", "1.0.0");
    PyModule_AddIntConstant(module, "year", 2025);

    return 0; /* success */
}

/*
 * Documentation for TestRepo1.
 */
PyDoc_STRVAR(TestRepo1_doc, "The TestRepo1 module");


static PyModuleDef_Slot TestRepo1_slots[] = {
    { Py_mod_exec, exec_TestRepo1 },
    { 0, NULL }
};

static PyModuleDef TestRepo1_def = {
    PyModuleDef_HEAD_INIT,
    "TestRepo1",
    TestRepo1_doc,
    0,              /* m_size */
    NULL,           /* m_methods */
    TestRepo1_slots,
    NULL,           /* m_traverse */
    NULL,           /* m_clear */
    NULL,           /* m_free */
};

PyMODINIT_FUNC PyInit_TestRepo1() {
    return PyModuleDef_Init(&TestRepo1_def);
}
