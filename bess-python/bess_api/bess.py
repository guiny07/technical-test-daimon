import numpy as np 
from ._bess_c import _lib, _BESS
import ctypes

def _check(code):
    if code != 0:
        err = _lib.bess_get_last_error()
        message = err.decode() if err else "Erro desconhecido"
        raise RuntimeError(message)


class BESS:
    def __init__(self):
        self.__handle = _lib.bess_create()

    def __del__(self):
        if self.__handle:
            _lib.bess_destroy(self.__handle)
            
    def set_curve(self, curve):
        curve = np.ascontiguousarray(curve, dtype=np.float64)

        code = _lib.bess_set_curve(
            self.__handle,
            curve.ctypes.data_as(ctypes.POINTER(ctypes.c_double)),
            len(curve)
        )
        _check(code)

    def set_dispatch(self, start, end):
        code = _lib.bess_set_dispatch_interval(self.__handle, start, end)
        _check(code)

    def run_dispatch(self):
        code = _lib.bess_run_dispatch(self.__handle)
        _check(code)

    @property
    def daily_energy(self):
        out = ctypes.c_double()
        code = _lib.bess_daily_energy(self.__handle, ctypes.byref(out))
        _check(code)
        return out.value

    @property
    def monthly_energy(self):
        out = ctypes.c_double()
        code = _lib.bess_monthly_energy(self.__handle, ctypes.byref(out))
        _check(code)
        return out.value

    def result_at(self, t):
        out = ctypes.c_double()
        code = _lib.bess_get_result_at(self.__handle, t, ctypes.byref(out))
        _check(code)
        return out.value

    @property
    def result_curve(self):
        out = np.zeros(24, dtype=np.float64)
        code = _lib.bess_get_result_curve(
            self.__handle,
            out.ctypes.data_as(ctypes.POINTER(ctypes.c_double)),
            24
        )
        _check(code)
        return out
