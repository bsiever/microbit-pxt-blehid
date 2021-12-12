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



#include "pxt.h"
#include "MicroBit.h"

#if CONFIG_ENABLED(DEVICE_BLE) 

#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_conn_params.h"
#include "ble_dis.h"

#include "HIDService.h"
#include "debug.h"


static HIDService *hids = NULL;

using namespace pxt;

namespace blehid { 

    void advertiseHID() {
        // m_advdata _must_ be static / retained!
        static ble_advdata_t m_advdata;
        // m_enc_advdata _must_ be static / retained!
        static uint8_t  m_enc_advdata[BLE_GAP_ADV_SET_DATA_SIZE_MAX];
        static ble_uuid_t uuid;  // UUID Struct
        uint8_t m_adv_handle;

        MICROBIT_DEBUG_DMESG( "configureAdvertising connectable %d, discoverable %d", (int) connectable, (int) discoverable);
        MICROBIT_DEBUG_DMESG( "whitelist %d, interval_ms %d, timeout_seconds %d", (int) whitelist, (int) interval_ms, (int) timeout_seconds);
        uuid.type = BLE_UUID_TYPE_BLE;
        uuid.uuid = 0x1812; //0x180D;  // 1812 sets to HID ; 180D Sets to Heart Rate
        m_advdata.uuids_complete.uuid_cnt = 1;
        m_advdata.uuids_complete.p_uuids = &uuid;
        m_advdata.include_appearance = true;
        // Name needed to be identified by Android
        m_advdata.name_type = BLE_ADVDATA_FULL_NAME;
        
        // Appearance isn't stricly needed for detection 
        sd_ble_gap_appearance_set(BLE_APPEARANCE_GENERIC_HID );
        /*
        Options for Advertised appearance:
            BLE_APPEARANCE_GENERIC_HID   960
            BLE_APPEARANCE_HID_KEYBOARD   961
            BLE_APPEARANCE_HID_MOUSE   962
            BLE_APPEARANCE_HID_JOYSTICK   963
            BLE_APPEARANCE_HID_GAMEPAD   964
         */

        // The flags below ensure "pairing mode" so it shows up in Android
        m_advdata.flags = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED | BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE;

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
        MICROBIT_BLE_ECHK( sd_ble_gap_adv_set_configure( &m_adv_handle, &gap_adv_data, &gap_adv_params));
    }

    //%
    void startHIDService() {
        // Start advertising as HID
#if CONFIG_ENABLED(DEVICE_BLE)
        DEBUG("advertising function\n");
        if(hids == NULL) {
            uBit.bleManager.stopAdvertising();
            advertiseHID();

            hids = new ::HIDService(*uBit.ble);

            // WARNING: This will start adv using the static handle in the BLE Manager. 
            // Hopefully the same handle is used as the one returned by sd_ble_gap_adv_set_configure
            uBit.bleManager.advertise();
       }
#endif
    }

    //% 
    void sendString(String keys) {
#if CONFIG_ENABLED(DEVICE_BLE)
        if(!hids) return;

        hids->sendString(keys->ascii.data, keys->ascii.length);
#endif
    }

    //%
    bool keyboardIsEnabled() {
        return hids ? hids->keyboardIsEnabled() : false;
    }

    //% 
    void setStatusChangeHandler(Action action) {
        DEBUG("Setting Status Changed Handler");
        registerWithDal(HIDService::EVT_ID, HIDService::EVT_STATUS, action);
        DEBUG("Done...");
    }

}


#else 

namespace blehid { 
    //%
    void startHIDService() {}
    //%
    void sendString(String keys) {}
    //%
    bool keyboardIsEnabled() { return false; }
    //%
    void setStatusChangeHandler(Action a) {}

}
#endif