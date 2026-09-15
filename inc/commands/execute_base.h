#ifndef RYUJINIII_EXECUTE_BASE_H
#define RYUJINIII_EXECUTE_BASE_H

/**
 * Default abstract class to be able to execute command and chains indistinctly
 */
class ExecuteBase {
public:
    /**
     * Default constructor
     */
    ExecuteBase() = default;
    /**
     * Default destructor
     */
    virtual ~ExecuteBase() = default;
    /**
     * Abstract method to be call indistinctly by commands and chains
     * @return True on success, otherwise false
     */
    virtual bool Execute() = 0;
    /**
     * Method used mainly for testing purposes
     * @return The class name as string
     */
    [[nodiscard]] virtual std::string GetClassName() const = 0;
};

#endif // RYUJINIII_EXECUTE_BASE_H
