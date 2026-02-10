#ifndef BESS_C_API_H
#define BESS_C_API_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BESSHandle BESSHandle;

BESSHandle* bess_create();
void bess_destroy(BESSHandle* handle);

void bess_set_curve(BESSHandle *handle, const double* curve, int size);
void bess_set_dispatch_interval(BESSHandle *handle, int start, int end);

void bess_discharge(BESSHandle *handle);

double bess_daily_energy(BESSHandle *handle);
double bess_monthly_energy(BESSHandle *handle);
double bess_get_result_at(BESSHandle *handle, int t);

void bess_get_result_curve(BESSHandle* handle, double* out_curve, int size);

#ifdef __cplusplus
}
#endif

#endif