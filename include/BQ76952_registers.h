#ifndef _BQ76952_REGISTERS_H
#define _BQ76952_REGISTERS_H

#include <stdint.h>

typedef struct fet_status {
    uint8_t             : 1;    // RSVD_0
    uint8_t ALRT_PIN    : 1;
    uint8_t DDSG_PIN    : 1;
    uint8_t DCHG_PIN    : 1;
    uint8_t PDSG_FET    : 1;
    uint8_t DSG_FET     : 1;
    uint8_t PCHG_FET    : 1;
    uint8_t CHG_FET     : 1;
} fet_status_t;

#endif  // #ifndef _BQ76952_REGISTERS_H
