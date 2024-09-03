#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "owb.h"
#include "comm.h"
#include "data.h"

#define OWB_SCALE ((float)100)
#define OWB_START_SEARCH_CODE ((uint8_t)0x77)

const CliCmdType CMD_OWB_READ =
{
	"owbrd",
	2,
	&doOwbRead,
	"  owbrd:            Read the temperature of the one 18b20 sensor\n",
	"  Usage:           "PROGRAM_NAME" <id> owbrd <channel> \n",
	"  Example:         "PROGRAM_NAME" 0 owbrd 1\n"
};
int doOwbRead(int argc, char *argv[])
{
	if (argc != 4)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0)
	{
		return ERROR;
	}
	int channel = atoi(argv[3]);
	uint8_t buff[2];
	if (OK != i2cMem8Read(dev, I2C_MEM_1WB_DEV, buff, 1))
	{
		printf("Fail to read!\n");
		return ERROR;
	}
	if (channel < 1 || channel > buff[0])
	{
		printf("Only %d sensors connected, select one of them!\n", (int)buff[0]);
		return ERROR;
	}
	if (OK != i2cMem8Read(dev, I2C_MEM_1WB_T1 + 2 * (channel - 1), buff, 2))
	{
		printf("Fail to read!\n");
		return ERROR;
	}
	int16_t vali;
	memcpy(&vali, buff, 2);
	float val = (float)vali / OWB_SCALE;
	printf("%0.2f\n", val);
	return OK;
}

const CliCmdType CMD_OWB_ID_READ =
{
	"owbidrd",
	2,
	&doOwbIdRead,
	"  owbidrd:          Read the 64-bits ID of the one 18b20 sensor\n",
	"  Usage:           "PROGRAM_NAME" <id> owbidrd <channel> \n",
	"  Example:         "PROGRAM_NAME" 0 owbidrd 1\n"
};
int doOwbIdRead(int argc, char *argv[])
{
	if (argc != 4)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0)
	{
		return ERROR;
	}
	int channel = atoi(argv[3]);
	uint8_t buff[8];
	if (OK != i2cMem8Read(dev, I2C_MEM_1WB_DEV, buff, 1))
	{
		printf("Fail to read!\n");
		return ERROR;
	}
	if (channel < 1 || channel > buff[0])
	{
		printf("Only %d sensors connected, select one of them!\n", (int)buff[0]);
		return ERROR;
	}
	buff[0] = (uint8_t)channel - 1;
	if (OK != i2cMem8Write(dev, I2C_MEM_1WB_ROM_CODE_IDX, buff, 1))
	{
		printf("Fail to write!\n");
		return ERROR;
	}
	if (OK != i2cMem8Read(dev, I2C_MEM_1WB_ROM_CODE, buff, 8))
	{
		printf("Fail to read!\n");
		return ERROR;
	}
	uint64_t id;
	memcpy(&id, buff, 8);
	printf("0x%lx\n", id);

	return OK;
}

const CliCmdType CMD_OWB_SNS_CNT_READ =
{
	"owbcrd",
	2,
	&doOwbSnsCntRd,
	"  owbcrd:          Read the number of sensors connected on the line\n",
	"  Usage:           "PROGRAM_NAME" <id> owbcrd\n",
	"  Example:         "PROGRAM_NAME" 0 owbcrd \n"
};
int doOwbSnsCntRd(int argc, char *argv[])
{
	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0)
	{
		return ERROR;
	}

	uint8_t buff[2];
	if (OK != i2cMem8Read(dev, I2C_MEM_1WB_DEV, buff, 1))
	{
		printf("Fail to read!\n");
		return ERROR;
	}
	printf("%d\n", (int)buff[0]);
	return OK;
}

const CliCmdType CMD_OWB_SCAN=
{
	"owbscan",
	2,
	&doOwbScan,
	"  owbscan:         Scan the bus for 18b20 sensors\n",
	"  Usage:           "PROGRAM_NAME" <id> owbscan \n",
	"  Example:         "PROGRAM_NAME" 0 owbscan\n"
};
int doOwbScan(int argc, char *argv[])
{
	if (argc != 3)
	{
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0)
	{
		return ERROR;
	}
	uint8_t buff[2];
	buff[0] = OWB_START_SEARCH_CODE;
	if (OK != i2cMem8Write(dev, I2C_MEM_1WB_START_SEARCH, buff, 1))
	{
		printf("Fail to write!\n");
		return ERROR;
	}
	printf("Start searching\n");

	return OK;
}
