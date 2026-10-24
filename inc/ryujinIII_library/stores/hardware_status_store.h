#ifndef RYUJINIII_HARDWARE_STATUS_STORE_H
#define RYUJINIII_HARDWARE_STATUS_STORE_H

/**
 * Hardware status store, which will hold all ryujin sensor data.
 * <br>Most methods are virtual to allow testing and mocking.
 */
class HardwareStatusStore {
public:
    /**
     * Default constructor
     */
    HardwareStatusStore() = default;
    /**
     * Default destructor
     */
    virtual ~HardwareStatusStore() = default;
    /**
     * Returns a float according to liquid temperature sensor data
     * @return the value of the liquid temperature
     */
    virtual const float GetLiquidTemp() const;
    /**
     * Returns a int according to pump speed sensor data
     * @return the value of the pump speed
     */
    virtual const int GetPumpSpeed() const;
    /**
     * Returns a int according to fan speed sensor data
     * @return the value of the fan speed
     */
    virtual const int GetFanSpeed() const;
    /**
     * Sets the value for liquid_temp_ property
     * @param liquid_temp the float value to set
     */
    virtual void SetLiquidTemp(float liquid_temp);
    /**
     * Sets the value for the pump_speed_ property
     * @param pump_speed the int value to set
     */
    virtual void SetPumpSpeed(int pump_speed);
    /**
     * Sets the value for the fan_speed_ property
     * @param fan_speed the int value to set
     */
    virtual void SetFanSpeed(int fan_speed);

private:
    /**
     * Property which holds the value for liquid temperature
     */
    float liquid_temp_ = 0.0f;
    /**
     * Property which holds the value for the pump speed
     */
    int pump_speed_ = 0;
    /**
     * Property which holds the value for the fan speed
     */
    int fan_speed_ = 0;
};

#endif // RYUJINIII_HARDWARE_STATUS_STORE_H
