import ctypes 
import numpy as np 
import os 

lib = ctypes.CDLL(os.path.abspath("../bess-core/build-DLL/libbess.so"))

lib.bess_create.restype = ctypes.c_void_p


lib.bess_set_curve.argtypes = [
    ctypes.c_void_p,
    ctypes.POINTER(ctypes.c_double),
    ctypes.c_int
]

lib.bess_set_dispatch_interval.argtypes = [
    ctypes.c_void_p,
    ctypes.c_int,
    ctypes.c_int
]

lib.bess_discharge.argtypes = [ctypes.c_void_p]

lib.bess_daily_energy.argtypes = [ctypes.c_void_p]
lib.bess_daily_energy.restype = ctypes.c_double

lib.bess_monthly_energy.argtypes = [ctypes.c_void_p]
lib.bess_monthly_energy.restype = ctypes.c_double

lib.bess_get_result_curve.argtypes = [
    ctypes.c_void_p,
    ctypes.POINTER(ctypes.c_double),
    ctypes.c_int
]

# Dados
curve = np.array([
    1.96887689, 1.140204703, 1.017916887, 0.93782698,
    0.957849457, 0.0, -0.397693755, -1.759566653,
    -3.440076817, -3.815379846, -4.316415417, -4.146073657,
    -3.95334117, -3.074246789, -1.756810872, -0.007061691,
    2.199027726, 3.122645206, 4.246272159, 4.869552487,
    4.161015161, 3.485633335, 2.328850882, 2.748461714
], dtype=np.float64)

# Uso
handle = lib.bess_create()

lib.bess_set_curve(handle, curve.ctypes.data_as(ctypes.POINTER(ctypes.c_double)), 24)
lib.bess_set_dispatch_interval(handle, 18, 24)
lib.bess_discharge(handle)

energy = lib.bess_daily_energy(handle)
print("Energia diária armazenada:", energy)

monthly_energy = lib.bess_monthly_energy(handle)
print("Energia mensal armazenada:", monthly_energy)

out = np.zeros(24, dtype=np.float64)
lib.bess_get_result_curve(handle, out.ctypes.data_as(ctypes.POINTER(ctypes.c_double)), 24)

print("Curva resultante:", out)

lib.bess_destroy(handle)