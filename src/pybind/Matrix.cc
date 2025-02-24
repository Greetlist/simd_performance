#include <pybind11/pybind11.h>

#include "defined_types.h"

namespace py = pybind11;

void init_matrix(py::module& m) {
  m.doc() = "matrix defination";
  py::class_<Matrix<float>>(m, "MatrixFloat")
    .def(py::init<int, int, float>())
    .def("GetRow", &Matrix<float>::GetRow)
    .def("GetCol", &Matrix<float>::GetCol)
    .def("Print", &Matrix<float>::Print);
}
