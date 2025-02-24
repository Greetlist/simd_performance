import os
import argh
import sys

current_dir = os.path.dirname(os.path.abspath(__file__))

#project_root_path = "$(pwd)/../../"
project_root_path = os.path.dirname(
    os.path.dirname(current_dir)
)
print(project_root_path)

build_path = os.path.join(project_root_path, "build/linux/x86_64/release/")
sys.path.append(build_path)

import libcalculator
def test_mul(row, col):
    cal_list = ["Base", "SSE", "AVX"]
    type_list = ["Float", "Double"]

    for c in cal_list:
        for t in type_list:
            cls = libcalculator.__dict__[c + "Calculator" + t]
            cls_instance = cls()
            if t == "Float":
                m1 = libcalculator.MatrixFloat(int(row), int(col), 1.00)
                m2 = libcalculator.MatrixFloat(int(row), int(col), 1.00)
            else:
                m1 = libcalculator.MatrixDouble(int(row), int(col), 1.00)
                m2 = libcalculator.MatrixDouble(int(row), int(col), 1.00)
            cls_instance.MatrixMul(m1, m2)

if __name__ == '__main__':
    argh.dispatch_commands([
        test_mul,
    ])
