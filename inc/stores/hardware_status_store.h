#ifndef RYUJINIII_HARDWARE_STATUS_STORE_H
#define RYUJINIII_HARDWARE_STATUS_STORE_H

class HardwareStatusStore {
public:
    HardwareStatusStore() = default;
    virtual ~HardwareStatusStore() = default;
    virtual const float GetLiquidTemp() const;
    virtual const int GetPumpSpeed() const;
    virtual const int GetFanSpeed() const;
    virtual void SetLiquidTemp(float liquid_temp);
    virtual void SetPumpSpeed(int pump_speed);
    virtual void SetFanSpeed(int fan_speed);

private:
    float liquid_temp_ = 0.0f;
    int pump_speed_ = 0;
    int fan_speed_ = 0;
};

#endif // RYUJINIII_HARDWARE_STATUS_STORE_H
