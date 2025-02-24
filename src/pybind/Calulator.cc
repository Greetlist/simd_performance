#include <pybind11/pybind11.h>

#include "AVXCalculator.h"
#include "BaseCalculator.h"
#include "defined_types.h"
#include "SSECalculator.h"

namespace py = pybind11;

void init_calculator(py::module& m) {
  py::class_<BaseCalculator<float>>(m, "BaseCalculatorFloat")
    .def(py::init<>())
    .def("MatrixMul", &BaseCalculator<float>::MatrixMul);
  py::class_<BaseCalculator<double>>(m, "BaseCalculatorDouble")
    .def(py::init<>())
    .def("MatrixMul", &BaseCalculator<double>::MatrixMul);

  py::class_<SSECalculator<float>>(m, "SSECalculatorFloat")
    .def(py::init<>())
    .def("MatrixMul", &SSECalculator<float>::MatrixMul);
  py::class_<SSECalculator<double>>(m, "SSECalculatorDouble")
    .def(py::init<>())
    .def("MatrixMul", &SSECalculator<double>::MatrixMul);

  py::class_<AVXCalculator<float>>(m, "AVXCalculatorFloat")
    .def(py::init<>())
    .def("MatrixMul", &AVXCalculator<float>::MatrixMul);
  py::class_<AVXCalculator<double>>(m, "AVXCalculatorDouble")
    .def(py::init<>())
    .def("MatrixMul", &AVXCalculator<double>::MatrixMul);
}
