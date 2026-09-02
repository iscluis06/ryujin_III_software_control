#ifndef RYUJINIII_FILE_HANDLE_H
#define RYUJINIII_FILE_HANDLE_H

#include <memory>
#include <string>
#include <vector>

/**
 * Helper class to manage file operations.
 */
class FileHandle {
public:
  /**
   * Default constructor
   */
  FileHandle() = default;

  /**
   * Constructor which initialize all properties by reading file specified
   * using path.
   * @param path Full path to file
   */
  FileHandle(const std::string &path);

  /**
   * Method which generates little endian hex representation
   * @return Returns size on hex format
   */
  std::vector<unsigned char> GetSizeToHex();

  /**
   * Buffer of read data on unsigned char (hex)
   */
  std::shared_ptr<unsigned char[]> buffer;
  /**
   * Current size on bytes of read file
   */
  int size;
  /**
   * Number of iterations required to send file data using bulk instruction
   * (4096)
   */
  int iterations;

private:
  /**
   * Method that reads all file data and initialize size, iterations and buffer.
   * @param path Path to file to read
   * @return True on success, false otherwise
   */
  bool ReadFile(const std::string &path);
};

#endif // RYUJINIII_FILE_HANDLE_H
