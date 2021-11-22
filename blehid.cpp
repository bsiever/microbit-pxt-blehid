/**
* Bill Siever
* 2021-11-20 Initial Version
*
* Development environment specifics:
* Written in Microsoft PXT
*
* This code is released under the [MIT License](http://opensource.org/licenses/MIT).
* Please review the LICENSE.md file included with this example. If you have any questions 
* or concerns with licensing, please contact techsupport@sparkfun.com.
* Distributed as-is; no warranty is given.
*/


// See https://github.com/kshoji/pxt-bluetooth-gamepad/blob/master/BluetoothGamepadService.cpp

//#define MICROBIT_CODAL 1  // Temp for  syntax highlighting


#include "pxt.h"
#include "MicroBit.h"

#if CONFIG_ENABLED(DEVICE_BLE) 

#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_conn_params.h"
#include "ble_dis.h"

#if MICROBIT_CODAL
#include "peripheral_alloc.h"
#endif 



// Copied from MicroBitBLEManager.cpp
static void const_ascii_to_utf8(ble_srv_utf8_str_t * p_utf8, const char * p_ascii)
{
    // ble_srv_ascii_to_utf8() doesn't check for p_ascii == NULL;
    // cast away const or allocate temporary buffer?
    p_utf8->p_str  = (uint8_t *)p_ascii;
    p_utf8->length = p_ascii ? (uint16_t)strlen(p_ascii) : 0;
}


#include "BatteryService.h"
#include "HIDService.h"
#include "debug.h"


static BatteryService *bs = NULL;
static HIDService *hids = NULL;

using namespace pxt;

namespace blehid { 

    void updateDIS() {
        // Copied from MicroBitBLEManager.cpp
//        MicroBitVersion version = uBit.power.getVersion();
        const char *MICROBIT_BLE_MANUFACTURER = NULL;
        static const char *MICROBIT_BLE_MODEL = "BBC micro:bit";
        const char *MICROBIT_BLE_HARDWARE_VERSION = NULL;
        const char *MICROBIT_BLE_FIRMWARE_VERSION = MICROBIT_DAL_VERSION;
        const char *MICROBIT_BLE_SOFTWARE_VERSION = NULL;
        // FIXME: Hardcoded, but should be based on board version as in MicroBit.cpp
        ManagedString modelVersion( "2.0");
        ManagedString disName( MICROBIT_BLE_MODEL);
        disName = disName + " V" + modelVersion;

        ble_dis_init_t disi;
        ble_dis_pnp_id_t pnp;
        memset( &pnp, 0, sizeof(pnp));
        memset( &disi, 0, sizeof(disi));
        disi.dis_char_rd_sec = SEC_OPEN;
        const_ascii_to_utf8( &disi.manufact_name_str,  MICROBIT_BLE_MANUFACTURER);
        const_ascii_to_utf8( &disi.model_num_str,      disName.toCharArray());
        const_ascii_to_utf8( &disi.serial_num_str,     uBit.getSerial().toCharArray());
        const_ascii_to_utf8( &disi.hw_rev_str,         MICROBIT_BLE_HARDWARE_VERSION);
        const_ascii_to_utf8( &disi.fw_rev_str,         MICROBIT_BLE_FIRMWARE_VERSION);
        const_ascii_to_utf8( &disi.sw_rev_str,         MICROBIT_BLE_SOFTWARE_VERSION);
        //ble_dis_sys_id_t *             p_sys_id;                    /**< System ID. */
        //ble_dis_reg_cert_data_list_t * p_reg_cert_data_list;        /**< IEEE 11073-20601 Regulatory Certification Data List. */
        // TODO update these:
        pnp.vendor_id_source = 1;
        pnp.vendor_id = 1;
        pnp.product_id = 1;
        pnp.product_version = 1;
        disi.p_pnp_id = &pnp;
        //ble_dis_pnp_id_t *             p_pnp_id;                    /**< PnP ID. */
        ble_dis_init( &disi);
    }


    void advertiseHID() {
#if MICROBIT_CODAL
        // TODO Do these need to be static???
        static ble_advdata_t m_advdata;
        static uint8_t  m_enc_advdata[BLE_GAP_ADV_SET_DATA_SIZE_MAX];
        static ble_uuid_t uuid;  // UUID Struct
        uint8_t m_adv_handle;


        // V2
        // destruct at old location
        DEBUG("advertising function\n");
        uBit.bleManager.stopAdvertising();

        MICROBIT_DEBUG_DMESG( "configureAdvertising connectable %d, discoverable %d", (int) connectable, (int) discoverable);
        MICROBIT_DEBUG_DMESG( "whitelist %d, interval_ms %d, timeout_seconds %d", (int) whitelist, (int) interval_ms, (int) timeout_seconds);
        uuid.type = BLE_UUID_TYPE_BLE;
        uuid.uuid = 0x1812; //0x180D;  // 1812 sets to HID ; 180D Sets to Heart Rate
        m_advdata.uuids_complete.uuid_cnt = 1;
        m_advdata.uuids_complete.p_uuids = &uuid;

        ble_gap_adv_params_t    gap_adv_params;
        memset( &gap_adv_params, 0, sizeof( gap_adv_params));
        gap_adv_params.properties.type  = true /* connectable */
                                        ? BLE_GAP_ADV_TYPE_CONNECTABLE_SCANNABLE_UNDIRECTED
                                        : BLE_GAP_ADV_TYPE_NONCONNECTABLE_SCANNABLE_UNDIRECTED;
        gap_adv_params.interval         = ( 1000 * MICROBIT_BLE_ADVERTISING_INTERVAL/* interval_ms */) / 625;  // 625 us units
        if ( gap_adv_params.interval < BLE_GAP_ADV_INTERVAL_MIN) gap_adv_params.interval = BLE_GAP_ADV_INTERVAL_MIN;
        if ( gap_adv_params.interval > BLE_GAP_ADV_INTERVAL_MAX) gap_adv_params.interval = BLE_GAP_ADV_INTERVAL_MAX;
        gap_adv_params.duration         = MICROBIT_BLE_ADVERTISING_TIMEOUT /* timeout_seconds */ * 100;              //10 ms units
        gap_adv_params.filter_policy    = false /* whitelist */
                                        ? BLE_GAP_ADV_FP_FILTER_BOTH
                                        : BLE_GAP_ADV_FP_ANY;
        gap_adv_params.primary_phy      = BLE_GAP_PHY_1MBPS;
                    
        ble_gap_adv_data_t  gap_adv_data;
        memset( &gap_adv_data, 0, sizeof( gap_adv_data));
        gap_adv_data.adv_data.p_data    = m_enc_advdata;
        gap_adv_data.adv_data.len       = BLE_GAP_ADV_SET_DATA_SIZE_MAX;


        MICROBIT_BLE_ECHK( ble_advdata_encode( &m_advdata, gap_adv_data.adv_data.p_data, &gap_adv_data.adv_data.len));
        //NRF_LOG_HEXDUMP_INFO( gap_adv_data.adv_data.p_data, gap_adv_data.adv_data.len);
        MICROBIT_BLE_ECHK( sd_ble_gap_adv_set_configure( &m_adv_handle, &gap_adv_data, &gap_adv_params));

        // WARNING: This will start adv using the static handle in the BLE Manager. 
        // Hopefully the same handle is used as the one returned by sd_ble_gap_adv_set_configure
        uBit.bleManager.advertise();
#endif

    }

    //%
    void startHIDService() {
        // Start advertising as HID
#if CONFIG_ENABLED(DEVICE_BLE)
        advertiseHID();
        if(bs == NULL) {
            updateDIS();
            bs = new ::BatteryService(*uBit.ble);
            hids = new ::HIDService(*uBit.ble);
        }
#endif
    }

    //% 
    void setBatteryLevel(uint8_t level) {
#if CONFIG_ENABLED(DEVICE_BLE)
        if(bs!=NULL) bs->setLevel(level);
#endif
    }
}
#else 

namespace blehid { 
    //%
    void startHIDService() {}
    //% 
    void setBatteryLevel(uint8_t level) {}
}
#endif