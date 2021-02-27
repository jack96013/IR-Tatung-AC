#include "IRTatungAC.h"
#include "IRTatungAcSetting.h"
#include "IRremoteESP8266.h"
#include <IRsend.h>
#include <IRrecv.h>
#include <math.h>


//const uint IRrawData[]={IRTatungAc_start1,IRTa};
const uint16_t IRTatungAc_header_mark = 3645;
const uint16_t IRTatungAc_header_space = 2300;
const uint16_t IRTatungAc_spilt = 8670;
const uint16_t IRTatungAc_0_mark = 640;
const uint16_t IRTatungAc_0_space = 640;
const uint16_t IRTatungAc_1_mark = 640;
const uint16_t IRTatungAc_1_space = 1700;

const uint16_t IRTatungAc_footer = 640; //footer (mark)
const uint16_t IRTatungAc_gap = 8000; //space
const uint16_t IRTatungAc_mesgtime = kDefaultMessageGap;
const uint16_t IRTatungAc_hz = 38;
const uint16_t IRTatungAc_duty = 30; //ir powrt 0-100
const uint16_t IRTatungAc_repeat = 1; //repeat again,two times
const uint16_t IRTatungAc_data_len = 31;

const uint8_t IRTatungAc_tolerance = 20;


uint64_t pow2(uint8_t p);

IRTatungAC::IRTatungAC()
{
    
}
bool IRTatungAC::begin(IRsend* ir)
{
    IRTatungAC::IRsender = ir;
    IRTatungAC::setting = new IRTatungAcSetting();
}
void  IRTatungAC::sendSetting()
{
    
    settingRaw_t raw = IRTatungAC::SettingToDataRaw(setting);
    IRsender->sendGeneric(IRTatungAc_header_mark, IRTatungAc_header_space,
                        IRTatungAc_1_mark, IRTatungAc_1_space ,
                        IRTatungAc_0_mark, IRTatungAc_0_space,
                        IRTatungAc_footer, IRTatungAc_gap,
                        IRTatungAc_mesgtime, raw,IRTatungAc_data_len, IRTatungAc_hz,false, IRTatungAc_repeat,IRTatungAc_duty);
}

settingRaw_t IRTatungAC::ResultToDataRaw(IRrecv *irrecv,decode_results *results)
{
    uint8_t tolerance = IRTatungAc_tolerance;
    uint8_t offset = 1;
    if (!match(irrecv,results,offset))
        return 0;
    if (results->bits != 2+IRTatungAc_data_len*2+2) //header (2) + len *2 + footer (2)
        return 0;
    
    settingRaw_t raw=0;
    uint8_t start_index = offset + 2;

    //uint8_t end_index = offset + 
    for (uint8_t i = 0;i<IRTatungAc_data_len;i++)
    {
        uint8_t current = start_index + i* 2;
        //Check the signal is bit 1 or 0
        bool bit_result;
        bool is_zero=true;
        bool is_one=true;
        if (!irrecv->matchMark(*(results->rawbuf +current),IRTatungAc_0_mark,tolerance,0))
            is_zero = false;         
        if (!irrecv->matchSpace(*(results->rawbuf + current+ 1),IRTatungAc_0_space,tolerance,0))
            is_zero = false;
        if (!irrecv->matchMark(*(results->rawbuf +current),IRTatungAc_1_mark,tolerance,0))
            is_one=false;
        if (!irrecv->matchSpace(*(results->rawbuf + current+ 1),IRTatungAc_1_space,tolerance,0))
            is_one=false;
        
        if (is_zero && !is_one) //is bit 0
            bit_result = 0;
        else if (!is_zero && is_one) //is bit 1
            bit_result = 1;
        else //unknown
            return 0;
        raw |= bit_result << i;
    }

    return raw;
}


bool IRTatungAC::match(IRrecv *irrecv,decode_results *results,uint8_t offset)
{
    uint8_t tolerance = IRTatungAc_tolerance;
    volatile uint16_t *data_ptr = results->rawbuf;
    //header
    if (IRTatungAc_header_mark && !irrecv->matchMark(*(results->rawbuf + offset),IRTatungAc_header_mark,tolerance,0))
        return false;
    if (IRTatungAc_header_space && !irrecv->matchSpace(*(results->rawbuf + offset+1),IRTatungAc_header_space,tolerance,0))
        return false;
    //footer  footer(mark) + gap(space)
    
    if (!irrecv->matchMark(*(results->rawbuf + offset+64),IRTatungAc_footer,tolerance,0))
        return false;
    if (!irrecv->matchSpace(*(results->rawbuf + offset+65),IRTatungAc_gap,tolerance,0))
        return false;
    return true;
}


settingRaw_t IRTatungAC::SettingToDataRaw(IRTatungAcSetting *setting)
{
    settingRaw_t raw=0;
    uint32_t raw_tmp;
    raw_tmp = setting->getPower();
    raw += raw_tmp << 1;
    raw_tmp = (uint32_t)setting->getMode();
    raw += raw_tmp << 3;
    raw_tmp = setting->getNatureSwing();
    raw += raw_tmp << 7;
    raw_tmp = setting->getSleepMode();
    raw += raw_tmp << 8;
    raw_tmp = setting->getTimingEnable();
    raw += raw_tmp << 10;
    raw += raw_tmp << 20;
    raw_tmp = (uint32_t)setting->getTiming();
    raw += raw_tmp << 11;
    
    raw_tmp = (uint32_t)setting->getFuzzy();
    raw += raw_tmp << 15;
    
    raw_tmp = setting->getTurbo();
    raw += raw_tmp << 17;
    raw_tmp = setting->getClean();
    raw += raw_tmp << 19;
    raw_tmp = setting->getHorizontalSwing();
    raw += raw_tmp << 21;
    raw_tmp = (uint32_t)setting->getSpeed();
    raw += raw_tmp << 23;
    raw_tmp = (uint32_t)setting->getTemperature();
    raw += raw_tmp << 26;
    
    raw += 1 << 2;
    raw += 1 << 30;

    //dataRaw
    return raw;
}

bool IRTatungAC::DataRawToSetting(settingRaw_t raw,IRTatungAcSetting* setting)
{
    if ((raw >> 2 & 1) && (raw >> 30 & 1))
    {
        setting->setPower(raw >> 1 & 1);
        setting->setMode(static_cast<IRTatungAcSetting::runMode_t>(raw >> 3 & 0x3));
        setting->setNatureSwing(raw >> 7 & 1);
        setting->setSleepMode(raw >> 8 & 1);
        setting->setTimingEnable((raw >> 10 & 1)&&(raw >> 20 & 1));
        setting->setTiming(static_cast<IRTatungAcSetting::timing_t>(raw >> 11 & 15));
        setting->setFuzzy(static_cast<IRTatungAcSetting::fuzzy_t>(raw >>15 & 3));
        setting->setTurbo(raw >> 17 & 1);
        setting->setClean(raw >> 19 & 1);
        setting->setHorizontalSwing(raw >> 21 & 1);
        setting->setSpeed(static_cast<IRTatungAcSetting::fan_speed_t>(raw >> 23 & 7));
        setting->setTemperature(static_cast<IRTatungAcSetting::temperature_t>(raw >> 26 & 15));
        return setting;
    }
    else
        return false;    
    
}

IRTatungAcSetting* IRTatungAC::getSetting()
{
    return IRTatungAC::setting;
}

void IRTatungAC::setSetting(IRTatungAcSetting *setting)
{
    if (IRTatungAC::setting != nullptr)
        free(IRTatungAC::setting);
    IRTatungAC::setting = setting;
}

uint64_t pow2(uint8_t p)
{
    uint64_t y=0;
    for (uint8_t i = 0 ; i < p ; p++)
    {
        y|=1;
        y<<=1;
    }
    return y;
}