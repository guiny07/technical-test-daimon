#include "bess_c_api.h"
#include "../BESS.h"
#include <vector>
#include  <string>

static thread_local std::string last_error;

struct BESSHandle {
    BESS instance;
};

// Métodos auxiliares para lidar com as exceções lançadas pelos métodos da classe BESS.
static int handle_exception(const std::exception& e){
    last_error = e.what();
    return -1;
}

const char* bess_get_last_error(){
    return last_error.c_str();
}


// Métodos da classe BESS.
BESSHandle* bess_create() {
    return new BESSHandle();
}

void bess_destroy(BESSHandle* handle) {
    delete handle;
}

int bess_set_curve(BESSHandle* handle, const double* curve, int size) {

    try{
        std::vector<double> v(curve, curve + size);
        handle->instance.setOriginalCurve(v);
        return 0;

    }
    catch (const std::exception& e){
        return handle_exception(e);
    }
}

int bess_set_dispatch_interval(BESSHandle* handle, int start, int end) {
    
    try{
        handle->instance.setDispatchInterval(start, end);
        return 0;
    }
    catch (const std::exception& e){
        return handle_exception(e);
    }
}

int bess_run_dispatch(BESSHandle* handle) {
    
    try{
        handle->instance.batteryDischarge();
        return 0;
    }
    catch (const std::exception& e){
        return handle_exception(e);
    }
}

int bess_daily_energy(BESSHandle* handle, double *out) {
    
    try{
        *out = handle->instance.getDailyStoredEnergy();
        return 0;
    }
    catch (const std::exception& e){
        return handle_exception(e);
    }
}

int bess_monthly_energy(BESSHandle* handle, double *out) {

    try{
        *out = handle->instance.getMonthlyStoredEnergy();
        return 0;
    }
    catch (const std::exception& e){
        return handle_exception(e);
    }
}

int bess_get_result_at(BESSHandle* handle, int t, double *out) {

    try{
        *out = handle->instance.getResultAt(t);
        return 0;
    }
    catch(const std::exception& e){
        return handle_exception(e);
    }
}

int bess_get_result_curve(BESSHandle* handle, double *out_curve, int size) {

    try{
        auto curve = handle->instance.getResultCurve();
        int n = std::min(size, (int)curve.size());
        for(int i = 0; i < n; i++)
            out_curve[i] = curve[i];
        return 0;
    }
    catch (const std::exception& e){
        return handle_exception(e);
    }
}