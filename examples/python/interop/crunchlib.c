/* Crunch turned into a trivial Python extension module */
/********************************************************/

#include <Python.h>

// Implement our crunch hash function in C
static unsigned int crunch(unsigned char *buff, unsigned int blen) {
    unsigned int i = 0;
    unsigned int val = 0xDEADBEEFL;

    for (; i < blen; ++i) {
        val += buff[i];
        val = ((val << 5) | (val >> 27)) & 0xffffffff;
    }

    return val;
}

/* The crunch-wrapper function (i.e., what gets called from Python):
    self: unused here, but required by the Python API
    args: all our Python arguments bundled together
 */
static PyObject *crunch_wrapper(PyObject *self, PyObject *args) {
    // We will access the bytes object in here
    Py_buffer buff = { 0 };
    unsigned int value = 0;

    // "Parse" the Python arguments to get our buffer object
    if (!PyArg_ParseTuple(args, "y*", &buff))
        return NULL;    // Exception happened; return NULL to raise it...

    // Compute the return value 
    value = crunch((unsigned char *)buff.buf, (unsigned int)buff.len);

    // Construct/return a Python integer value
    return Py_BuildValue("I", value);
}

/* Module registration table */
static struct PyMethodDef crunch_methods[] = {
    { "crunch", crunch_wrapper, 1 },
    { NULL, NULL }
};

/* Module definition structure */
static struct PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT,
    "crunchlib",
    "This is a demonstration of how awesome Python and C are together.",
    0,
    crunch_methods,
    NULL,
    NULL,
    NULL,
    NULL
};

/* Module initialization function */
PyObject *PyInit_crunchlib() {
    return PyModule_Create(&module_def);
}

