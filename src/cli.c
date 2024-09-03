
#include "board.h"
#include "cli.h"
#include "comm.h"
#include "help.h"
#include "wdt.h"
#include "button.h"
#include "owb.h"


const CliCmdType *gCmdArray[] = {
	&CMD_HELP,
	&CMD_VERSION,
	&CMD_BOARD,
	&CMD_WDT_RELOAD,
	&CMD_WDT_GET_PERIOD,
	&CMD_WDT_SET_PERIOD,
	&CMD_WDT_GET_INIT_PERIOD,
	&CMD_WDT_SET_INIT_PERIOD,
	&CMD_WDT_GET_OFF_PERIOD,
	&CMD_WDT_SET_OFF_PERIOD,
	&CMD_WDT_GET_RESET_COUNT,
	&CMD_WDT_CLR_RESET_COUNT,
	&CMD_BUTTON_READ,
	&CMD_BUTTON_LATCH_READ,
	&CMD_OWB_READ,
	&CMD_OWB_ID_READ,
	&CMD_OWB_SNS_CNT_READ,
	&CMD_OWB_SCAN,
	0
};
