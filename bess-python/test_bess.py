from bess_api import BESS
import numpy as np

bess = BESS()

curve = np.array([
    1.96887689, 1.140204703, 1.017916887, 0.93782698,
    0.957849457, 0.0, -0.397693755, -1.759566653,
    -3.440076817, -3.815379846, -4.316415417, -4.146073657,
    -3.95334117, -3.074246789, -1.756810872, -0.007061691,
    2.199027726, 3.122645206, 4.246272159, 4.869552487,
    4.161015161, 3.485633335, 2.328850882, 2.748461714
], dtype=np.float64)

# set da curva original no objeto
bess.set_curve(curve)

print(f"Energia diária armazenada: {bess.get_daily_energy:.2f}")
print(f"Energia mensal armazenada: {bess.get_monthly_energy:.2f}")

bess.set_dispatch(17, 5)
print("Intervalo de despacho definido das 17h às 05h.")