#ifndef BESS_C_API_H
#define BESS_C_API_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BESSHandle BESSHandle;

BESSHandle* bess_create();
void bess_destroy(BESSHandle* handle);

int bess_set_curve(BESSHandle *handle, const double* curve, int size);
int bess_set_dispatch_interval(BESSHandle *handle, int start, int end);

int bess_run_dispatch(BESSHandle *handle);

int bess_daily_energy(BESSHandle *handle, double *out);
int bess_monthly_energy(BESSHandle *handle, double *out);
int bess_get_result_at(BESSHandle *handle, int t, double *out);

int bess_get_result_curve(BESSHandle* handle, double *out_curve, int size);

const char* bess_get_last_error();

#ifdef __cplusplus
}
#endif

#endif