import os
import argh
import sys
import numpy as np
import time
import datetime as dt

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
    cal_list = ["SSE", "AVX"]
    type_list = ["Float", "Double"]
    row = int(row)
    col = int(col)

    for c in cal_list:
        for t in type_list:
            cls = libcalculator.__dict__[c + "Calculator" + t]
            cls_instance = cls()
            if t == "Float":
                m1 = libcalculator.MatrixFloat(row, col, 1.00)
                m2 = libcalculator.MatrixFloat(col, row, 1.00)
            else:
                m1 = libcalculator.MatrixDouble(row, col, 1.00)
                m2 = libcalculator.MatrixDouble(col, row, 1.00)
            cls_instance.MatrixMul(m1, m2)

    np_m1 = np.full((row, col), 1.00, dtype='float32')
    np_m2 = np.full((col, row), 1.00, dtype='float32')

    start = time.time()
    np.dot(np_m1, np_m2)
    end = time.time()
    print((end - start) * 1000 * 1000)

if __name__ == '__main__':
    argh.dispatch_commands([
        test_mul,
    ])
