#include <stdio.h>
#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_11_API_VERSION
#include <numpy/arrayobject.h>
#include "integrate.h"


static char module_docstring[] = 
    "This module provides an interface for calculating numeric integrals";
static char riemann_docstring[] = 
    "Calculate the integral by Riemann Sum";
static char trapezoid_docstring[] = 
    "Calculate the integral by Trapezoid Sum";

static PyObject *integrate_riemann(PyObject *self, PyObject *args);
static PyObject *integrate_trapezoid(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
    {"riemann", integrate_riemann, METH_VARARGS, riemann_docstring},
    {"trapezoid", integrate_trapezoid, METH_VARARGS, trapezoid_docstring},
    {NULL, NULL, 0, NULL}};

PyMODINIT_FUNC init_integrate(void)
{
    PyObject *m = Py_InitModule3("_integrate", module_methods, 
               module_docstring);

    // return if there was a problem
    if(m == NULL)
        return;

    // Load numpy stuff!
    import_array();
}

static PyObject *integrate_riemann(PyObject *self, PyObject *args)
{
    double a, b;
    int N;
    PyObject *fi_obj = NULL;

    //Parse arguments
    if(!PyArg_ParseTuple(args, "Oddi", &fi_obj, &a, &b, &N))
        return NULL;

    //Grab numpy array
    PyArrayObject *fi_arr;
    fi_arr = (PyArrayObject *) PyArray_FROM_OTF(fi_obj, 
                                        NPY_DOUBLE, NPY_ARRAY_IN_ARRAY);
    
    // Throw exception
    if(fi_arr == NULL)
    {
        Py_XDECREF(fi_arr);
        return NULL;
    }
    
    // Here's the actual array!
    double *fi = (double *) PyArray_DATA(fi_arr);

    //Here's the function!
    double I = riemann(fi, a, b, N);

    //Clean!
    Py_DECREF(fi_arr);

    //Build output
    PyObject *ret = Py_BuildValue("d", I);
    return ret;
}

static PyObject *integrate_trapezoid(PyObject *self, PyObject *args)
{
    double a, b;
    int N;
    PyObject *fi_obj = NULL;

    //Parse arguments
    if(!PyArg_ParseTuple(args, "Oddi", &fi_obj, &a, &b, &N))
        return NULL;

    //Grab numpy array
    PyArrayObject *fi_arr;
    fi_arr = (PyArrayObject *) PyArray_FROM_OTF(fi_obj, 
                                        NPY_DOUBLE, NPY_ARRAY_IN_ARRAY);

    // Throw exception
    if(fi_arr == NULL)
    {
        Py_XDECREF(fi_arr);
        return NULL;
    }
    
    // Here's the actual array!
    double *fi = (double *) PyArray_DATA(fi_arr);

    //Here's the function!
    double I = trapezoid(fi, a, b, N);

    //Clean!
    Py_DECREF(fi_arr);

    //Build output
    PyObject *ret = Py_BuildValue("d", I);
    return ret;
}
