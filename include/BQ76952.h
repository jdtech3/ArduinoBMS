#ifndef _BQ76952_H
#define _BQ76952_H

#include <Arduino.h>
#include <Wire.h>

#include "BQ76952_registers.h"
#include "BQ76952_commands.h"

#define I2C_ADDR            0x08
#define REG_SUBCMD_LOWER    0x3E
#define REG_SUBCMD_UPPER    0x3F
#define REG_TRANSFER_BUF    0x40
#define REG_CHECKSUM        0x60
#define REG_DATA_LEN        0x61


enum CMD_TYPE { DIRECT, SUBCMD_COMMAND, SUBCMD_DATA };

class BQ76952 {
    public:
        BQ76952();
        BQ76952(byte);
        void begin();
        void reset();
        void send_cmd(CMD_TYPE, uint16_t);
        fet_status_t get_fet_status();
        void set_fets(bool);
        void fet_enable();
        bool check_connection();
    private:
        byte _i2c_addr;
        byte _direct_cmd_resp_buf[2];
        byte _xfer_buf[32];

        void _send_direct_cmd(byte, uint8_t);
        int _send_subcmd(uint16_t, bool);
        bool _block_until_subcmd_complete(uint16_t);
        int _read_subcmd_data(byte, byte);
};

#endif  // #ifndef _BQ76952_H
