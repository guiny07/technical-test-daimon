import ctypes 
import os 

_current_dir = os.path.dirname(os.path.abspath(__file__))

_lib_path = os.path.abspath(
    os.path.join(_current_dir, "../../bess-core/build-DLL/libbess.so")
)

_lib = ctypes.CDLL(_lib_path)

class _BESS(ctypes.Structure):
    pass

# Retorno e argumentos de cada método da classe BESS no C++

_lib.bess_create.argtypes = []
_lib.bess_create.restype = ctypes.POINTER(_BESS)

_lib.bess_destroy.argtypes = [ctypes.POINTER(_BESS)]

_lib.bess_set_curve.argtypes = [
    ctypes.POINTER(_BESS),
    ctypes.POINTER(ctypes.c_double),
    ctypes.c_int
]
_lib.bess_set_curve.restype = ctypes.c_int

_lib.bess_set_dispatch_interval.argtypes = [
    ctypes.POINTER(_BESS),
    ctypes.c_int,
    ctypes.c_int
]
_lib.bess_set_dispatch_interval.restype = ctypes.c_int

_lib.bess_run_dispatch.argtypes = [ctypes.POINTER(_BESS)]
_lib.bess_run_dispatch.restype = ctypes.c_int

_lib.bess_daily_energy.argtypes = [ctypes.POINTER(_BESS), ctypes.POINTER(ctypes.c_double)]
_lib.bess_daily_energy.restype = ctypes.c_int

_lib.bess_monthly_energy.argtypes = [ctypes.POINTER(_BESS), ctypes.POINTER(ctypes.c_double)]
_lib.bess_monthly_energy.restype = ctypes.c_int

_lib.bess_get_result_at.argtypes = [ctypes.POINTER(_BESS), ctypes.c_int, ctypes.POINTER(ctypes.c_double)]
_lib.bess_get_result_at.restype = ctypes.c_int

_lib.bess_get_result_curve.argtypes = [
    ctypes.POINTER(_BESS),
    ctypes.POINTER(ctypes.c_double),
    ctypes.c_int
]
_lib.bess_get_result_curve.restype = ctypes.c_int

_lib.bess_get_last_error.argtypes = []
_lib.bess_get_last_error.restype = ctypes.c_char_p

