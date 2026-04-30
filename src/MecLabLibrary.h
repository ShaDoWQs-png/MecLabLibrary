#include "util/Managers.hpp"
#include <P1AM.h>
#pragma once

/**
 * @class Motor
 * @brief A class to control a motor
 * @details This class allows you to control a motor by moving it forward, reversing it, and stopping it. It also allows you to check the current direction of the motor (forward, reverse, or off).
 * @param slot The slot where the motor is connected (usually 1)
 * @param port The port where the motor is connected (1-10)
 * @param revPort The second port used to reverse the motor (1-10)
 */
class Motor {
    public:
        enum class MotorState {
          REVERSE = -1,
          OFF = 0,
          FORWARD = 1
        };

        /**
         * @param slot The slot where the motor is connected (usually 1)
         * @param port The port where the motor is connected (1-10)
         * @param revPort The second port used to reverse the motor (1-10)
         */
        Motor(const int slot, const int port, const int revPort);

        /**
         * @brief Moves the motor forward
         */
        void forward();
        /** @param durationMs The duration to move the motor forward in milliseconds */
        void forward(int durationMs);

        /**
         * @brief Moves the motor in reverse
         */
        void reverse();
        /** @param durationMs The duration to move the motor in reverse in milliseconds */
        void reverse(int durationMs);

        /**
         * @brief Stops the motor
         */
        void stop();
        /** @param durationMs The duration to stop the motor in milliseconds */
        void stop(int durationMs);

        /**
         * @brief Returns the current state of the motor (forward, reverse, or off)
         * @return The current state of the motor (as a MotorState type)
         */
        MotorState direction();

    private:
        int _timerHandle = -1;
        int _slot;
        int _port; 
        int _revPort;
        MotorState state;
};

/**
 * @class OpticalSensor
 * @brief A class to read from an optical sensor
 * @param slot The slot where the sensor is connected (usually 1)
 * @param port The port where the sensor is connected (1-10)
 */
class OpticalSensor {
    public:
        /**
         * @param slot The slot where the sensor is connected (usually 1)
         * @param port The port where the sensor is connected (1-10)
         */
        OpticalSensor(const int slot, const int port);

        /**
         * @brief Reads the value from the optical sensor
         * @return true if the sensor is triggered, false if not
         */
        bool read();

        int getPort();

    private:
        int _slot;
        int _port;
};

/**
 * @class Solenoid
 * @brief A class to control a solenoid
 * @details This class allows you to control a solenoid by extending and retracting it, as well as checking if it is currently extended.
 * @param slot The slot where the solenoid is connected (usually 1)
 * @param port The port where the solenoid is connected (1-10)
 */
class Solenoid {
    public:
        /**
         * @param slot The slot where the solenoid is connected (usually 1)
         * @param port The port where the solenoid is connected (1-10)
         */
        Solenoid(const int slot, const int port);

        /**
         * @brief Extends the solenoid
         */
        void extend();
        /** @param durationMs The duration to extend the solenoid in milliseconds */
        void extend(int durationMs);

        /**
         * @brief Retracts the solenoid
         */
        void retract();
        /** @param durationMs The duration to retract the solenoid in milliseconds */
        void retract(int durationMs);

        /**
         * @brief Checks if the solenoid is currently extended
         * @return true if the solenoid is extended, false if it is retracted
         */
        bool isExtended();

        int getPort();

    private:
        int _slot;
        int _port;
        bool _isExtended;
        int _timerHandle = -1;
};

/**
 * @class ReedSwitch
 * @brief A class to read from a reed switch 
 * @param slot The slot where the switch is connected (usually 1)
 * @param port The port where the switch is connected (1-10)
 */
class ReedSwitch {
    public:
        ReedSwitch(const int slot, const int port);

        bool read();

        int getPort();

    private:
        int _slot;
        int _port;
};

/**
 * @class InductionSensor
 * @brief A class to read from an induction sensor
 * @param slot The slot where the sensor is connected (usually 1)
 * @param port The port where the sensor is connected (1-10)
 */
class InductionSensor {
    public:
        /**
         * @param slot The slot where the sensor is connected (usually 1)
         * @param port The port where the sensor is connected (1-10)
         */
        InductionSensor(const int slot, const int port);

        /**
         * @brief Reads the value from the induction sensor
         * @return true if the sensor is triggered, false if not
         */
        bool read();

        int getPort();

    private:
        int _slot;
        int _port;
};

/**
 * @class PneumaticValve
 * @brief A class to control a pneumatic valve using two solenoids
 * @details This class allows you to control a pneumatic valve by extending and retracting it using two solenoids. It also keeps track of the current state of the valve (extending, extended, retracting, or retracted).
 * @param slot The slot where the valve is connected (usually 1)
 * @param portA The first solenoid port used for valve (1-10)
 * @param portB The second solenoid port used for valve (1-10)
 */
class PneumaticValve {
  public:
    enum class ValveState {
        OFF,
        EXTENDING,
        EXTENDED,
        RETRACTING,
        RETRACTED
    };

  private:
    int _slot;
    int _portA;
    int _portB;
    Solenoid solA;
    Solenoid solB;
    ReedSwitch* reedRet = nullptr;
    ReedSwitch* reedExt = nullptr;
    ValveState state;
    int _timerHandle = -1;
    bool reedSwitches = false;
    unsigned long stateTimer;
    ValveState lastMoveCall = ValveState::OFF;

    void updateState(ValveState changeState);

  public:
    //Extension time in ms
    float extensionTime = 500;
    //Retraction time in ms
    float retractionTime = 500;
    
    /**
     * @param slot The slot where the valve is connected (usually 1)
     * @param portA The first solenoid port used for valve (1-10)
     * @param portB The second solenoid port used for valve (1-10)
     */
    PneumaticValve(const int slot, const int portA, const int portB);

    /**
     * @param slot The slot where the valve is connected (usually 1)
     * @param portA The first solenoid port used for valve (1-10)
     * @param portB The second solenoid port used for valve (1-10)
     * @param reedExtPort The reed switch that is on when the cylindar is extended
     * @param reedRetPort The reed switch that is on when the cylindar is retracted
     */
    PneumaticValve(const int slot, const int portA, const int portB, const int reedExtPort, const int reedRetPort);

    /**
     * @brief Updates the valve so that it can move. This should be called in a loop to allow the valve to function properly.
     */
    void update();

    /**
     * @brief Extends the valve
     */
    void extend();
    /** @param durationMs The duration to extend the valve in milliseconds */
    void extend(int durationMs);

    /**
     * @brief Retracts the valve
     */
    void retract();
    /** @param durationMs The duration to retract the valve in milliseconds */
    void retract(int durationMs);

    /**
     * @brief Turns the valve off
     */
    void off();

    /**
     * @brief Returns the current state of the valve
     * @return The current state of the valve
     */
    ValveState getState();
};

/**
 * @class Vaccuum
 * @brief Class to control the vaccum on the arm
 * @param slot The slot where the vaccuum is connected
 * @param port the port where the vaccuum is connected
 */
class Vaccuum {
    private:
        int _slot;
        int _port;
        bool TheSucker;
    
    public:
        /**
         * @brief Initializes the Vaccuum
         * @param slot Slot of the vaccuum
         * @param port Port of the vaccuum
         */
        Vaccuum(const int slot, const int port);

        /**
         * @brief turns the vaccuum on
         */
        void suck();

        /**
         * @brief turns the vaccuum on
         */
        void notsuck();

        /**
         * @brief gets whether the vaccum is on or off
         * @return true if on, false if off
         */
        bool getState();
};

class SuctionArm {
    private:
        PneumaticValve* _valveY;
        PneumaticValve* _valveX;
        Vaccuum* _vac;

    public:
        enum class Direction{
            LEFT,
            RIGHT
        };

        SuctionArm(PneumaticValve& valveX, PneumaticValve& valveY, Vaccuum& vac);

        void pick();

        void place();

        void transferObject();
};

bool getButtonPress(int slot, int port);