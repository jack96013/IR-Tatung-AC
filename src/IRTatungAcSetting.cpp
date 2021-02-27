#ifndef IR_TATUNG_H_
#define IR_TATUNG_H_

#include "IRTatungAcSetting.h"
#include <Arduino.h>

IRTatungAcSetting::IRTatungAcSetting()
{
    ;
}

void IRTatungAcSetting::setDefault()
{
    
    ;
}

String boolToString(bool);

String* IRTatungAcSetting::getInfo()
{
    String *info = new String();
    info->reserve(300);
    *info += F("=====INFO=====\npower ");
    *info += boolToString(getPower());
    *info += F("\ntiming enable\t");
    *info += boolToString(getTimingEnable());
    *info += F("\nhorizontal swing\t");
    *info += boolToString(getHorizontalSwing());
    *info += F("\nnature swing\t");
    *info += boolToString(getNatureSwing());
    *info += F("\nturbo\t\t");
    *info += boolToString(getTurbo());
    *info += F("\nsleep mode\t");
    *info += boolToString(getSleepMode());
    *info += F("\nclean\t\t");
    *info += boolToString(getClean());
    *info += F("\nmode\t\t");
    *info += convertModeToString(getMode()); 
    *info += F("\ntimging\t\t");
    *info += convertTimingToFloat(getTiming());
    *info += F("\ntemperature\t");
    *info += convertTemperatureToInt(getTemperature());
    *info += F("\nfuzzy\t\t");
    *info += convertFuzzyToString(getFuzzy());
    *info += F("\nspeed\t\t");
    *info += convertSpeedToString(getSpeed());
    *info += F("\n==============\n");
    return info;
}

String IRTatungAcSetting::convertModeToString(runMode_t mode)
{
    String out= "";
    out.reserve(20);
    switch (mode)
    {
        case runMode_t::fullAuto:
            out = F("Full Auto");
            break;
        case runMode_t::cool:
            out = F("Cool");
            break;
        case runMode_t::dry:
            out = F("Dry");
            break;
        case runMode_t::fan:
            out = F("Fan");
            break;
    }
    out += " (";
    out += (uint8_t)mode;
    out += ")";
    return out;

}
float IRTatungAcSetting::convertTimingToFloat(timing_t timing)
{
    if ((uint8_t)timing == 15)
    {
        return 0.5f;
    }
    else
    {
        return (uint8_t)timing;
    }
}
uint8_t IRTatungAcSetting::convertTemperatureToInt(temperature_t temperature)
{
    return (uint8_t)temperature+16u;
}
String IRTatungAcSetting::convertFuzzyToString(fuzzy_t fuzzy)
{
    String out="";
    out.reserve(20);
    switch (fuzzy)
    {
        case fuzzy_t::so_cold:
            out = F("So Cold");
            break;
        case fuzzy_t::normal:
            out = F("Normal");
            break;
        case fuzzy_t::so_hot:
            out = F("So Hot");
            break;
    }
    out += " (";
    out += (uint8_t)fuzzy;
    out += ")";
    return out;
}
String IRTatungAcSetting::convertSpeedToString(fan_speed_t speed)
{
    String out="";
    out.reserve(20);
    switch (speed)
    {
        case fan_speed_t::auto_spd:
            out = F("Auto Speed");
            break;
        case fan_speed_t::micro:
            out = F("Micro");
            break;
        case fan_speed_t::low:
            out = F("Low");
            break;
        case fan_speed_t::strong:
            out = F("Strong");
            break;
    }
    out += " (";
    out += (uint8_t)speed;
    out += ")";
    return out;
}

bool IRTatungAcSetting::getPower()
{
    return power;
}
bool IRTatungAcSetting::getTimingEnable()
{
    return timing_enable;
}
bool IRTatungAcSetting::getHorizontalSwing()
{
    return horizontal_swing;
}
bool IRTatungAcSetting::getNatureSwing()
{
    return nature_swing;
}
bool IRTatungAcSetting::getTurbo()
{
    return turbo;
}
bool IRTatungAcSetting::getSleepMode()
{
    return sleep_mode;
}
bool IRTatungAcSetting::getClean()
{
    return clean;
}
IRTatungAcSetting::runMode_t IRTatungAcSetting::getMode()
{
    return mode;
}
IRTatungAcSetting::timing_t IRTatungAcSetting::getTiming()
{
    return timing;
}
IRTatungAcSetting::temperature_t IRTatungAcSetting::getTemperature()
{
    return temperature;
}
IRTatungAcSetting::fuzzy_t IRTatungAcSetting::getFuzzy()
{
    return fuzzy;
}

IRTatungAcSetting::fan_speed_t IRTatungAcSetting::getSpeed()
{
    return speed;
}

void IRTatungAcSetting::setPower(bool on)
{
    power = on;
}
void IRTatungAcSetting::setTimingEnable(bool enable)
{
    timing_enable = enable;
}
void IRTatungAcSetting::setHorizontalSwing(bool enable)
{
    horizontal_swing = enable;
}
void IRTatungAcSetting::setNatureSwing(bool enable)
{
    nature_swing = enable;
}
void IRTatungAcSetting::setTurbo(bool enable)
{
    turbo = enable;
}
void IRTatungAcSetting::setSleepMode(bool enable)
{
    sleep_mode = enable;
}
void IRTatungAcSetting::setClean(bool enable)
{
    clean = enable;
}
void IRTatungAcSetting::setMode(runMode_t _mode)
{
    mode = _mode;
}
void IRTatungAcSetting::setTiming(timing_t time)
{
    timing = time;
}
void IRTatungAcSetting::setTemperature(temperature_t temp)
{
    temperature = temp;
}
void IRTatungAcSetting::setFuzzy(fuzzy_t fuzzy_mode)
{
    fuzzy = fuzzy_mode;
}

void IRTatungAcSetting::setSpeed(fan_speed_t fan_speed)
{
    speed = fan_speed;
}

String boolToString(bool k)
{
    return k?F("true"):F("false");
}

#endif