import numpy as np 
from ._bess_c import _lib, _BESS
import ctypes


class BESS:
    def __init__(self):
        self.__handle = _lib.bess_create()

    def __del__(self):
        if self.__handle:
            _lib.bess_destroy(self.__handle)
    
    def set_curve(self, curve):
        curve = np.asarray(curve, dtype=np.float64)
        _lib.bess_set_curve(
            self.__handle,
            curve.ctypes.data_as(ctypes.POINTER(ctypes.c_double)),
            len(curve)
        )

    def set_dispatch(self, start, end):
        _lib.bess_set_dispatch_interval(self.__handle, start, end)
    
    def run_dispatch(self):
        _lib.bess_run_dispatch(self.__handle)

    @property
    def get_daily_energy(self):
        return _lib.bess_daily_energy(self.__handle)
    
    @property
    def get_monthly_energy(self):
        return _lib.bess_monthly_energy(self.__handle)
    
    @property
    def get_result_at(self, t):
        return _lib.bess_get_result_at(self.__handle, t)

    @property
    def get_result_curve(self):
        out = np.zeros(24, dtypes=np.float64)
        _lib.bess_get_result_curve(
            self.__handle,
            out.ctypes.data_as(ctypes.POINTER(ctypes.c_double)),
            24
        )
        return out