#include<Arduino.h>
#include"def.h"
#pragma once



class mymotor{
    public:
        void attach(uint8_t ma, uint8_t mb, uint8_t pwmPin, uint8_t csPin, uint8_t encInterrPin, uint8_t encDirectPin, float kprop);
        // void write(int speed);
        // void write2(int speed2);
        void power(int vel);
        void statWrite(int val);
        int getK(){return _kprop;}

        void setEnc(int32_t encoder){_mEncoder += encoder;}
        void resetEnc(){_mEncoder = 0; _timerEnc = 0;}
        int32_t getEnc(){return _mEncoder;}
        uint16_t getCS(){return analogRead(_csPin);}

    private:
        uint8_t _ma, _mb, _pwmPin, _csPin, _encInterrPin, _encDirectPin;
        float _kprop;
        uint32_t _timerEnc = millis();
        int32_t _mEncoder = 0;
};





class mytelega{
    public:
        mymotor _motor0;
        mymotor _motor1;
        mymotor _motor2;
        mymotor _motor3;
        mymotor _motor4;
        mymotor _motor5;
        void encSens();
        void csSens();
        void set(mymotor motor0, mymotor motor1, mymotor motor2, mymotor motor3, mymotor motor4, mymotor motor5){
            _motor0 = motor0;
            _motor1 = motor1;
            _motor2 = motor2;
            _motor3 = motor3;
            _motor4 = motor4;
            _motor5 = motor5;
        }
        // void start(){
        //     static bool allStart = 0;
        //     while (!allStart)
        //     {
        //         //if(_motor0.getCS() < START_CS0){_motor0.write(START_SPEED);}
        //         if(_motor1.getCS() < START_CS1){_motor1.write(START_SPEED);}
        //         if(_motor2.getCS() < START_CS2){_motor2.write(START_SPEED);}
        //         if(_motor3.getCS() < START_CS3){_motor3.write(START_SPEED);}
        //         if(_motor4.getCS() < START_CS4){_motor4.write(START_SPEED);}
        //         if(_motor5.getCS() < START_CS5){_motor5.write(START_SPEED);}
                
        //     if (/*!(_motor0.getCS() < START_CS0)&&*/
        //         !(_motor1.getCS() < START_CS1)&&
        //         !(_motor2.getCS() < START_CS2)&&
        //         !(_motor3.getCS() < START_CS3)&&
        //         !(_motor4.getCS() < START_CS4)&&
        //         !(_motor5.getCS() < START_CS5)){
        //         allStart = 1;
        //        }
        //     }
            
        //}
    private:
        // void allMotor(int val){
        //     _motor0.write(val);
        //     _motor1.write(val);
        //     _motor2.write(val);
        //     _motor3.write(val);
        //     _motor4.write(val);
        //     _motor5.write(val);
        // }
};
