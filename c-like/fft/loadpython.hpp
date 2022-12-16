#pragma once
#include <iostream>
#include <python3.9/Python.h>

class LoadPy {
private:
  void getlist(PyObject* l, int len, double *a) {
    for (int i = 0; i < len; i++) {
      PyList_SetItem(l, i, Py_BuildValue("d", a[i]));
    }
  }

public:
  void runpy(double *x, double *y1, double *y2, int len) {
    Py_Initialize();

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    PyObject* pModule = PyImport_ImportModule("draw");
    PyObject* pFunc = PyObject_GetAttrString(pModule, "draw");

    PyObject* px = PyList_New(len);
    getlist(px, len, x);
    PyObject* py1 = PyList_New(len);
    getlist(py1, len, y1);
    PyObject* py2 = PyList_New(len);
    getlist(py2, len, y2);

    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, px);
    PyTuple_SetItem(args, 1, py1);
    PyTuple_SetItem(args, 2, py2);

    PyObject_CallObject(pFunc, args);

    Py_DECREF(pModule);
    Py_DECREF(pFunc);
    Py_DECREF(px);
    Py_DECREF(py1);
    Py_DECREF(py2);
    Py_DECREF(args);

    Py_Finalize();
  }
};
