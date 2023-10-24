#include "BQ76952.h"

// Constructor: default I2C addr
BQ76952::BQ76952() { _i2c_addr = I2C_ADDR; }

// Constructor: user defined I2C addr
BQ76952::BQ76952(byte addr) { _i2c_addr = addr; }

// External
void BQ76952::begin() {
    Wire.begin(_i2c_addr);
    memset(_direct_cmd_resp_buf, 0, 2 * sizeof(byte));     // ensure bufs are zeroed
    memset(_xfer_buf, 0, 32 * sizeof(byte));
}

void BQ76952::set_fets(bool on) {
    _send_subcmd(on ? CMD_ALL_FETS_ON : CMD_ALL_FETS_OFF, false);
}

void BQ76952::fet_enable() {
    _send_subcmd(CMD_FET_ENABLE, false);
}

fet_status_t BQ76952::get_fet_status() {
    _send_direct_cmd(CMD_FET_STATUS, 1);
    
    fet_status_t status = {
        .ALRT_PIN = _direct_cmd_resp_buf[0] & 0b01000000,
        .DDSG_PIN = _direct_cmd_resp_buf[0] & 0b00100000,
        .DCHG_PIN = _direct_cmd_resp_buf[0] & 0b00010000,
        .PDSG_FET = _direct_cmd_resp_buf[0] & 0b00001000,
        .DSG_FET  = _direct_cmd_resp_buf[0] & 0b00000100,
        .PCHG_FET = _direct_cmd_resp_buf[0] & 0b00000010,
        .CHG_FET  = _direct_cmd_resp_buf[0] & 0b00000001,
    };

    return status;
}

// Internal
void BQ76952::_send_direct_cmd(byte cmd, uint8_t output_size) {
    byte buf[2] = { 0 };    // output is always either 1 or 2 byte
    Wire.beginTransmission(_i2c_addr);
    Wire.write(cmd);
    Wire.endTransmission();

    if (output_size > 0) {
        Wire.requestFrom(_i2c_addr, output_size);
        Wire.readBytes(buf, output_size);
        if (output_size == 2) Serial.println(buf[1], HEX);
        Serial.println(buf[0], HEX);
        memcpy(_direct_cmd_resp_buf, buf, 2);   // copy to class level
    }   
}

int BQ76952::_send_subcmd(uint16_t subcmd, bool returns_data) {
    byte subcmd_lsb = subcmd & 0x00FF;
    byte subcmd_msb = subcmd >> 8;

    Wire.beginTransmission(_i2c_addr);
    Wire.write(REG_SUBCMD_LOWER);
    Wire.write(subcmd_lsb);    // block write
    Wire.write(subcmd_msb);
    Wire.endTransmission();

    if (returns_data) {
        Serial.println(_block_until_subcmd_complete(subcmd) ? "true" : "false");
        return _read_subcmd_data(subcmd_msb, subcmd_lsb);
    }
    
    return 0;
}

int BQ76952::_read_subcmd_data(byte subcmd_msb, byte subcmd_lsb) {
    byte buf[32] = { 0 };
    char out_buf[3];
    
    // Read response length
    Wire.beginTransmission(_i2c_addr);
    Wire.write(REG_DATA_LEN);
    Wire.endTransmission();

    Wire.requestFrom(_i2c_addr, 1);
    byte len = Wire.read();
    len -= 4;       // "0x61 provides length plus 4"

    // Read into buf
    Wire.beginTransmission(_i2c_addr);
    Wire.write(REG_TRANSFER_BUF);
    Wire.endTransmission();

    Wire.requestFrom(_i2c_addr, len);
    Wire.readBytes(buf, len);

    Serial.println("START");
    for (int i = 0; i < 32; i++) {
        // sprintf(out_buf, "%02x", buf[i]);
        Serial.println(buf[i], HEX);
    }
    Serial.println("STOP");

    // Check checksum
    byte checksum = subcmd_lsb + subcmd_msb + len;  // 8 bit sum of subcommand bytes and xfer buffer bytes
    checksum = ~checksum;                           // then invert

    Wire.beginTransmission(_i2c_addr);
    Wire.write(REG_CHECKSUM);
    Wire.endTransmission();

    Wire.requestFrom(_i2c_addr, 1);
    byte expected_checksum = Wire.read();

    if (checksum != expected_checksum) {
        return -1;
    }
    else {
        memcpy(_xfer_buf, buf, len);    // good to go, copy to class level
        return (int) len;
    }
}

bool BQ76952::_block_until_subcmd_complete(uint16_t subcmd) {
    uint16_t resp;
    char out_buf[5];
    do {
        Wire.beginTransmission(_i2c_addr);
        Wire.write(REG_SUBCMD_LOWER);
        Wire.endTransmission();     // can alternatively do a repeated start here

        Wire.requestFrom(_i2c_addr, 2);
        
        byte resp_lsb = Wire.read();
        byte resp_msb = Wire.read();

        resp = 0x0000;          // reset
        resp |= resp_msb;       // reassemble 2 byte subcommand
        resp <<= 8;
        resp |= resp_lsb;
    } while (resp == 0xFFFF);
    sprintf(out_buf, "%04x", resp);
    Serial.println(out_buf);
    return resp == subcmd;  // return success (ignore if command only subcommand)
}

bool BQ76952::check_connection() {
    // check for magic (device number)
    // TODO!
    
    // // delay(500);
    // // char out_buf[16];
    // // _send_subcmd(0x001F, false);
    // // _send_subcmd(0x0020, false);
    // // _send_direct_cmd(0x64, 2);
    // // delay(1000);
    // // _send_direct_cmd(0x7F, 1);
    // // _send_direct_cmd(0x7F, 1);
    // // delay(1000);
    // // _send_subcmd(0x0057, true);
    // // delay(1000);
    // // _send_subcmd(0x0022, false);
    // // delay(1000);
    // // _send_subcmd(0x0057, true);
    // // delay(1000);
    // // _send_subcmd(0x0096, false);
    // // delay(1000);
    // // _send_subcmd(0x001F, false);    // CHG
    // // _send_subcmd(0x0020, false); // DSG
    // delay(100);
    // _send_direct_cmd(0x7F, 1);
    // delay(10);
    // _send_subcmd(0x0022, false);
    // delay(10);
    // _send_subcmd(0x0096, false);
    // delay(1000);
    // _send_direct_cmd(0x7F, 1);
    // delay(5000);
    // while (1) {
    //     _send_subcmd(0x0075, true);
    //     delay(60000);
    // }
        
    // int bytes_read = _send_subcmd(0x0057, true);
    // if (bytes_read > 0) {
    //     for (int i = 0; i < bytes_read; i++) {
    //         sprintf(out_buf, "%02x\n", _xfer_buf[i]);
    //         Serial.print(out_buf);
    //     }
    // }
    return true;
}
