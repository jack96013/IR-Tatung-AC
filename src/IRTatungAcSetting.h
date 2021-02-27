#ifndef IR_TatungSetting_H_
#define IR_TatungSetting_H_
#include <Arduino.h>
class IRTatungAcSetting
{
    public:
        explicit IRTatungAcSetting();
        void setDefault();

        enum class runMode_t:uint8_t //2bit
        {
            fullAuto=0,
            cool=1,
            dry=2,
            fan=3,
        };

        enum class timing_t:uint8_t //4bit
        {
            h0_5=15,
            h1=1,
            h2=2,
            h3=3,
            h4=4,
            h5=5,
            h6=6,
            h7=7,
            h8=8,
            h9=9,
            h10=10,
            h11=11,
            h12=12,
        };

        enum class temperature_t:uint8_t //4bit
        {
            t17=1,
            t18=2,
            t19=3,
            t20=4,
            t21=5,
            t22=6,
            t23=7,
            t24=8,
            t25=9,
            t26=10,
            t27=11,
            t28=12,
            t29=13,
            t30=14,
            t31=15,
            t32=16,
        };
        enum class fuzzy_t:uint8_t //2bit
        {
            so_cold = 1,
            normal = 2,
            so_hot = 3,
        };

        enum class fan_speed_t:uint8_t //3bit
        {
            auto_spd=0,
            micro=1,
            low=2,
            strong=4,
        };

        String *getInfo();

        runMode_t convertModeFromInt();
        timing_t convertTimingFromFloat();
        temperature_t convertTemperatureFromInt();
        fuzzy_t convertFuzzyFromString();
        fan_speed_t convertSpeedFromString();

        bool getPower();
        bool getTimingEnable();
        bool getHorizontalSwing();
        bool getNatureSwing(); 
        bool getTurbo();
        bool getSleepMode(); 
        bool getClean();

        runMode_t getMode();
        timing_t getTiming();
        temperature_t getTemperature();
        fuzzy_t getFuzzy();
        fan_speed_t getSpeed();

        void setPower(bool on);
        void setTimingEnable(bool enable);
        void setHorizontalSwing(bool enable);
        void setNatureSwing(bool enable); 
        void setTurbo(bool enable);
        void setSleepMode(bool enable); 
        void setClean(bool enable);

        void setMode(runMode_t mode);
        void setTiming(timing_t time);
        void setTemperature(temperature_t temp);
        void setFuzzy(fuzzy_t fuzzy_mode);
        void setSpeed(fan_speed_t);

        static String convertModeToString(runMode_t);
        static float convertTimingToFloat(timing_t);
        static uint8_t convertTemperatureToInt(temperature_t);
        static String convertFuzzyToString(fuzzy_t);
        static String convertSpeedToString(fan_speed_t);
        

    private:
        bool power = false;
        bool timing_enable = false;
        bool horizontal_swing = false;
        bool nature_swing = false;
        bool turbo = false;
        bool sleep_mode = false;
        bool clean = false;

        runMode_t mode=runMode_t::fullAuto;
        timing_t timing=timing_t::h0_5;
        temperature_t temperature=temperature_t::t25;
        fuzzy_t fuzzy=fuzzy_t::normal;
        fan_speed_t speed=fan_speed_t::auto_spd;

        
};
#endif