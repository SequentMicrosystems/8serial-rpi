#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "comm.h"
#include "data.h"

const CliCmdType CMD_BOARD = {
        "board",
        2,
        &doBoard,
        "  board            Display the board status and firmware version number\n",
        "  Usage:           "PROGRAM_NAME" <stack> board\n",
        "  Example:         "PROGRAM_NAME" 0 board  Display vcc, temperature, firmware version \n"

};
int doBoard(int argc, char *argv[]) {
        if(argc != 3) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(atoi(argv[1]));
        if(dev <= 0) {
                return ERROR;
        }
        uint8_t buf[5];
        if(OK != i2cMem8Read(dev, I2C_MEM_DIAG_TEMPERATURE_ADD, buf, 5)) {
                printf("Fail to read board info!\n");
                return ERROR;
        }
        uint8_t temperature = buf[0];
        uint16_t resp;
        memcpy(&resp, &buf[3], 2);
        float vMbus = (float)resp / VOLT_TO_MILIVOLT; //read in milivolts
        memcpy(&resp, &buf[1], 2);
        float vRasp = (float)resp / VOLT_TO_MILIVOLT; //read in milivolts
        if(ERROR == i2cMem8Read(dev, I2C_MEM_REVISION_MAJOR_ADD, buf, 2)) {
                printf("Fail to read board info!\n");
                return ERROR;
        }
        printf("Firmware version %d.%d, CPU temperature %d C, M-Bus %0.2f V, Raspberry %0.2f V\n",
                (int)buf[0], (int)buf[1], temperature, vRasp, vMbus);
        return OK;
}

// vi:fdm=marker
