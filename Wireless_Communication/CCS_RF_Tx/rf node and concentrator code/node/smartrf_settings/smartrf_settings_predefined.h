#ifndef _SMARTRF_SETTINGS_PREDEFINED_H_
#define _SMARTRF_SETTINGS_PREDEFINED_H_


//*********************************************************************************
// Generated by SmartRF Studio version 2.12.0 (build #128)
// Tested for SimpleLink SDK version: CC13x2 SDK 2.30.xx.xx
// Device: CC1352R Rev. 2.1
//
//*********************************************************************************


#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/rf_mailbox.h)
#include DeviceFamily_constructPath(driverlib/rf_common_cmd.h)
#include DeviceFamily_constructPath(driverlib/rf_prop_cmd.h)

#include <ti/drivers/rf/RF.h>


// TX Power table size definition
#define RF_PROP_TX_POWER_TABLE_SIZE 20

// TX Power Table Object
extern RF_TxPowerTable_Entry RF_PROP_txPowerTable[];


/* RF Core API commands */
/* RF command pointers for easylink */
extern RF_Mode RF_prop_fsk;
extern RF_Mode RF_prop_sl_lr;
extern RF_Mode RF_prop_fsk_200kbps;

extern rfc_CMD_PROP_RADIO_DIV_SETUP_t RF_cmdPropRadioDivSetup_fsk;
extern rfc_CMD_PROP_RADIO_DIV_SETUP_t RF_cmdPropRadioDivSetup_sl_lr;
extern rfc_CMD_PROP_RADIO_DIV_SETUP_t RF_cmdPropRadioDivSetup_fsk_200kbps;

extern rfc_CMD_FS_t RF_cmdFs_preDef;
extern rfc_CMD_PROP_TX_ADV_t RF_cmdPropTxAdv_preDef;
extern rfc_CMD_PROP_RX_ADV_t RF_cmdPropRxAdv_preDef;

extern uint32_t pOverrides_fsk[];
extern uint32_t pOverrides_sl_lr[];
extern uint32_t pOverrides_fsk_200kbps[];

#endif // _SMARTRF_SETTINGS_PREDEFINED_H_
