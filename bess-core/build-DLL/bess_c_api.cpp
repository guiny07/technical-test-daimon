#include "bess_c_api.h"
#include "../BESS.h"
#include <vector>

struct BESSHandle {
    BESS instance;
};

BESSHandle* bess_create() {
    return new BESSHandle();
}

void bess_destroy(BESSHandle* handle) {
    delete handle;
}

void bess_set_curve(BESSHandle* handle, const double* curve, int size) {
    if(size != 24) return;

    std::vector<double> v(curve, curve + size);
    handle->instance.setOriginalCurve(v);
}

void bess_set_dispatch_interval(BESSHandle* handle, int start, int end) {
    handle->instance.setDispatchInterval(start, end);
}

void bess_run_dispatch(BESSHandle* handle) {
    handle->instance.batteryDischarge();
}

double bess_daily_energy(BESSHandle* handle) {
    return handle->instance.getDailyStoredEnergy();
}

double bess_monthly_energy(BESSHandle* handle) {
    return handle->instance.getMonthlyStoredEnergy();
}

double bess_get_result_at(BESSHandle* handle, int t) {
    return handle->instance.getResultAt(t);
}

void bess_get_result_curve(BESSHandle* handle, double* out_curve, int size) {
    if(size != 24) return;

    auto curve = handle->instance.getResultCurve();
    for(int i = 0; i < 24; i++)
        out_curve[i] = curve[i];
}
