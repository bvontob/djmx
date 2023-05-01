#include "usermodfx.h"

static float amp_r;
static uint32_t pchg = 0;

void MODFX_INIT(uint32_t platform, uint32_t api) {
  (void)platform; (void)api;
  pchg  = 0;
  amp_r = 0.5f;
}

void MODFX_PROCESS(const float *main_xn, float *main_yn,
                   const float *sub_xn, float *sub_yn,
                   uint32_t frames) {
  (void)*sub_xn; (void)*sub_yn;
  
  for (uint32_t i = 0; i < frames; i++) {
    const float in_l   = main_xn[i * 2];
    const float in_r   = main_xn[i * 2 + 1];

    const float out_m  = in_l * (1.0f - amp_r) + in_r * amp_r;
    
    main_yn[i * 2]     = out_m;
    main_yn[i * 2 + 1] = out_m;
  }
}

void MODFX_PARAM(uint8_t idx, int32_t val) {
  /* Ignore the first parameter changes to keep our defaults */
  if (pchg++ < 4)
    return;

  const float val_f = q31_to_f32(val);

  switch (idx) {
  case k_user_modfx_param_time:
    break;
  case k_user_modfx_param_depth:
    amp_r = val_f;
    break;
  default:
    break;
  }
}
