#ifndef IR_TATUNG_H_
#define IR_TATUNG_H_

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#ifdef ARDUINO
#include <Arduino.h>
#endif
#include "IRremoteESP8266.h"
#include "IRsend.h"
#include "IRrecv.h"
#ifdef UNIT_TEST
#include "IRsend_test.h"
#endif

#include "IRTatungAcSetting.h"

//us
//Command Format [Start1 Start2 | Spilt | Repeat ]

typedef uint32_t settingRaw_t;

class IRTatungAC
{
    public:
        IRTatungAC();
        bool begin(IRsend*);

        void sendSetting();
        settingRaw_t ResultToDataRaw(IRrecv *irrecv,decode_results *result);
        bool match(IRrecv *irrecv,decode_results *results,uint8_t offset);

        IRTatungAcSetting* getSetting();
        void setSetting(IRTatungAcSetting*);
        static settingRaw_t SettingToDataRaw(IRTatungAcSetting*);
        static bool DataRawToSetting(settingRaw_t , IRTatungAcSetting*);
    private:
        IRsend *IRsender;
        IRTatungAcSetting* setting;
        settingRaw_t settingRaw;
        
};

#endif