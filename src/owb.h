#ifndef OWB_H
#define OWB_H

#include "cli.h"

extern const CliCmdType CMD_OWB_READ;
extern const CliCmdType CMD_OWB_ID_READ;
extern const CliCmdType CMD_OWB_SNS_CNT_READ;
extern const CliCmdType CMD_OWB_SCAN;

int doOwbRead(int argc, char *argv[]);
int doOwbIdRead(int argc, char *argv[]);
int doOwbSnsCntRd(int argc, char *argv[]);
int doOwbScan(int argc, char *argv[]);

#endif /* BUTTON_H */
