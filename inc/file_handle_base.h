#ifndef RYUJINIII_FILE_HANDLE_BASE_H
#define RYUJINIII_FILE_HANDLE_BASE_H

#include <memory>
#include <string>
#include <vector>

class FileHandleBase {
public:
    /**
     * Default constructor
     */
    FileHandleBase() = default;

    /**
     * Destructor
     */
    virtual ~FileHandleBase() = default;

    /**
     * Initializer routine, will execute read file and set all properties
     */
    bool Initialize();

    /**
     * Method which generates little endian hex representation
     * @return Returns size on hex format
     */
    std::vector<unsigned char> GetSizeToHex();

    /**
     * Getter for read data
     * @return Const reference to read data
     */
    const std::shared_ptr<unsigned char[]> GetBuffer() const;
    /**
     * Getter for size
     * @return Const reference to size
     */
    const int GetSize() const;
    /**
     * Getter for iterations
     * @return Const reference to iterations
     */
    const int GetIterations() const;
    /**
     * Getter to path
     * @return Reference to path
     */
    const std::string GetPath() const;
    /**
     * Setter for buffer
     * @param buffer Reference to buffer
     */
    void SetBuffer(const std::shared_ptr<unsigned char[]> &buffer);
    /**
     * Setter for size
     * @param size Value to set
     */
    void SetSize(int size);
    /**
     * Setter for iterations
     * @param iterations Value to set
     */
    void SetIterations(int iterations);
    /**
     * Setter to path
     * @param path Path to file
     */
    void SetPath(const std::string &path);

protected:
    /**
     * Method that reads all file data and initialize size, iterations and buffer.
     * @param path Path to file to read
     * @return True on success, false otherwise
     */
    virtual bool ReadFile() = 0;

private:
    /**
     * Buffer of read data on unsigned char (hex)
     */
    std::shared_ptr<unsigned char[]> buffer_;
    /**
     * Current size on bytes of read file
     */
    int size_;
    /**
     * Number of iterations required to send file data using bulk instruction
     * (4096)
     */
    int iterations_;
    /**
     * Reference to the path of file
     */
    std::string path_;
};

#endif // RYUJINIII_FILE_HANDLE_BASE_H
