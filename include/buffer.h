/**
 * @file buffer.h
 *
 * @brief General purpose buffer
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <stdlib.h>
#ifndef ARDUINO
#include <string>
#endif



namespace syndesi {

#ifdef ARDUINO
using string_t = String;
#else
using string_t = std::string;
#endif

#ifdef ARDUINO
// Use the String class
#define INT_TO_STRING(x) (x)
#else
#define INT_TO_STRING(x) std::to_string(x)
#endif

/**
 * @brief Buffer class
 *
 */
class Buffer {
    class rawBuffer {
       private:
        char* _data = nullptr;
        size_t _length = 0;
        // Buffer is defined externaly and not managed
        bool external = false;

       public:
        rawBuffer(){};
        rawBuffer(size_t length) {
            _data = (char*)malloc(length);
            if (_data == nullptr) {
                // throw std::bad_alloc();
            } else {
                _length = length;
            }
        };
        ~rawBuffer() {
            if (_data != nullptr && !external) {
                free((char*)_data);
            }
        };
        rawBuffer(char* buffer, size_t length) {
            _data = buffer;
            _length = length;
            external = true;
        };

        char* start() { return _data; };
        size_t length() const { return _length; };
    };

   public:
    /**
     * @brief Construct a new empty Buffer object with size length
     *
     * @param length
     */
    Buffer();
    Buffer(size_t length);
    ~Buffer();
    Buffer(Buffer* parent, size_t offset, size_t length = 0);
    Buffer(char* buffer, size_t length);

   private:
    size_t _total_offset = 0;
    size_t _offset = 0;
    rawBuffer* _data = nullptr;
    size_t _clipLength = 0;

   public:
    void allocate(size_t length);

    void deallocate();

    /**
     * @brief Create a subbuffer (with an offset compared to the first one)
     *
     * @param parent the parent buffer
     * @param offset the start offset of the data
     */
    void fromParent(const Buffer* parent, size_t offset, size_t length = 0);

    /**
     * @brief Init with the given buffer
     *
     * @param buffer
     * @param length
     */
    void fromBuffer(char* buffer, size_t length);

    /**
     * @brief Create a sub-buffer
     *
     * @param offset offset from start
     * @param length length of sub-buffer (default to max)
     */
    Buffer offset(size_t offset, size_t length = 0);

    size_t length() const;

    /**
     * @brief Get the raw data pointer
     *
     */
    char* data() const { return _data->start() + _offset; };

    /**
     * @brief Get the sub-buffer offset (from base buffer)
     *
     * @return size_t
     */
    size_t getOffset();

    /**
     * @brief Export buffer as string
     *
     */
    char* toString();

    /**
     * @brief Export buffer as hex string (12 F1 8A ...)
     *
     */
    string_t toHex();
};
}  // namespace syndesi

#endif  // BUFFER_H
