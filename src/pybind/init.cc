#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_matrix(py::module&);
void init_calculator(py::module&);

PYBIND11_MODULE(libcalculator, m) {
  m.doc() = "SSE/AVX SpeedUp Calculator";
  init_matrix(m);
  init_calculator(m);
}
