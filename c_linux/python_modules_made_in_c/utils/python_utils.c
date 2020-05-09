/*
 * =====================================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/07/20 11:28:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <Python.h>

int fatorial(int n) {
	if (n == 0) {
		return 1;
	} else if (n < 0) {
		return -1;
	}

	int resultado = n;

	while (--n) {
		resultado *= n;
	}

	return resultado;
}

static PyObject *py_fatorial(PyObject *self, PyObject *value) {
	//Funções para trabalhar com conversão de números: https://docs.python.org/3.6/c-api/long.html
	int n = PyLong_AsLong(value);
	if (n == 0) {
		return PyLong_FromLong(1);
	} else if (n < 0) {
		return PyLong_FromLong(-1);
	}

	int resultado = n;

	while (--n) {
		resultado *= n;
	}

	return PyLong_FromLong(resultado);
}

PyDoc_STRVAR(fatorial_doc, "Retorna o fatorial do primeiro parâmetro");
const PyMethodDef fatorial_method = {
	"fatorial",
	(PyCFunction) py_fatorial,
	METH_O,//um único parâmetro, mais em: https://docs.python.org/3/c-api/structures.html
	fatorial_doc,
};

static PyObject *py_pow(PyObject *self, PyObject *args) {
	int base;
	int expoente;

	//z == string, char *, None == NULL
	//b == integer(char)
	//i == int
	//f == float
	//d == double
	//o == objeto, PyObject *
	//Mais sobre PyArg_ParseTuple em https://docs.python.org/2.0/ext/parseTuple.html
	if (!PyArg_ParseTuple(args, "ii", &base, &expoente))
		//caso a quantidade de parâmetros seja diferente de 2 uma exceção é gerada
		return NULL;

	if (expoente == 0) {
		return PyLong_FromLong(1);
	}

	int resultado = base;

	while (--expoente) {
		resultado *= base;
	}

	return PyLong_FromLong(resultado);
}

PyDoc_STRVAR(pow_doc, "Retorna a potência, do primeiro argumento(base), elevado ao segundo argumento(expoente)");
const PyMethodDef pow_method = {
	"pow",
	(PyCFunction) py_pow,
	METH_VARARGS,//Mais de um parâmetro, mais em: https://docs.python.org/3/c-api/structures.html
	pow_doc,
};

PyObject *py_get_pi(PyObject *self) {
	//Funções que envolvem float, https://docs.python.org/3/c-api/float.html
	return PyFloat_FromDouble(3.14159265359);
}

PyDoc_STRVAR(py_pi_doc, "Uma função sem argumentos que retorna o número pi");
const PyMethodDef get_pi_method = {
	"pi",
	(PyCFunction) py_get_pi,
	METH_NOARGS,//0 parâmetros, mais em: https://docs.python.org/3/c-api/structures.html
	py_pi_doc,
};

static PyObject *py_kw_pow(PyObject *self, PyObject *args, PyObject *kw) {
	int base;
	int expoente;

	//z == string, char *, None == NULL
	//b == integer(char)
	//i == int
	//f == float
	//d == double
	//o == objeto, PyObject *
	//Mais em https://docs.python.org/2.0/ext/parseTuple.html
	
	char *parametros[] = {"base", "expoente", NULL};
	//mais sobre PyArg_ParseTupleAndKeywords em https://docs.python.org/2.0/ext/parseTupleAndKeywords.html e
	//https://docs.python.org/3/c-api/arg.html#c.PyArg_ParseTupleAndKeywords
	if (!PyArg_ParseTupleAndKeywords(args, kw, "ii", parametros, &base, &expoente))
		//caso a quantidade de parâmetros seja diferente de 2 uma exceção é gerada
		return NULL;

	if (expoente == 0) {
		return PyLong_FromLong(1);
	}

	int resultado = base;

	while (--expoente) {
		resultado *= base;
	}

	return PyLong_FromLong(resultado);
}

PyDoc_STRVAR(kw_pow_doc, "Retorna a potência, do primeiro argumento(base), elevado ao segundo argumento(expoente)");
const PyMethodDef kw_pow_method = {
	"kw_pow",
	(PyCFunction) py_kw_pow,
	METH_VARARGS | METH_KEYWORDS,//Mais de um parâmetro, mais em: https://docs.python.org/3/c-api/structures.html
	kw_pow_doc,
};

PyObject *py_raise_exception(PyObject *self) {
	//standard exceptions: https://docs.python.org/3.6/c-api/exceptions.html#standard-exceptions
	PyErr_SetString(PyExc_KeyboardInterrupt, "exceção de teclado");
	PyErr_SetString(PyExc_ImportError, "erro no import");
	PyErr_SetString(PyExc_Exception, "uma exceção genérica foi lançada");
	return NULL;
}

PyDoc_STRVAR(raise_exc_doc, "Uma função que lança uma exceção");
const PyMethodDef raise_exc_method = {
	"raise_exception",
	(PyCFunction) py_raise_exception,
	METH_NOARGS,//Nenhum parâmetro, https://docs.python.org/3/c-api/structures.html
	raise_exc_doc,
};

PyObject *py_soma_lista(PyObject *self, PyObject *lista) {
	//Funções relacionadas a Listas https://docs.python.org/3.6/c-api/list.html
	if (!(PyList_Check(lista))) {
		PyErr_SetString(PyExc_TypeError, "não é uma lista");
		return NULL;
	}
	Py_ssize_t length = PyList_Size(lista);
	int i;
	int result = 0;
	for (i = 0; i < length; i++) {
		PyObject * elemento = PyList_GetItem(lista, (Py_ssize_t)i);
		if (!PyLong_Check(elemento)) {
			PyErr_SetString(PyExc_TypeError, "não é inteiro");
			return NULL;
		} else {
			result += PyLong_AsLong(elemento);
		}
	}
	return PyLong_FromLong(result);
}

PyDoc_STRVAR(soma_lista_doc, "uma função que soma os números inteiros de uma lista.");
const PyMethodDef soma_lista_method = {
	"soma_lista",
	(PyCFunction) py_soma_lista,
	METH_O,//Um único parâmetro, https://docs.python.org/3/c-api/structures.html
	soma_lista_doc,
};

static struct PyMethodDef methods[] = {
	fatorial_method,
	pow_method,
	get_pi_method,
	kw_pow_method,
	raise_exc_method,
	soma_lista_method,
	{NULL, NULL, 0, NULL}
};

PyDoc_STRVAR(utils_module_doc, "Um módulo com funções utilitárias");
static struct PyModuleDef utils_module = {
	PyModuleDef_HEAD_INIT,
	"utils",
	utils_module_doc,
	-1,
	methods
};

PyMODINIT_FUNC PyInit_utils(void) {
	return PyModule_Create(&utils_module);
}
