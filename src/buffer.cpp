/**
 * @file buffer.cpp
 *
 * @brief General purpose buffer
 *
 * @author Sébastien Deriaz
 * @date 16.08.2022
 */

#include "buffer.h"

namespace syndesi {

Buffer::Buffer() { _total_offset = 0; }

Buffer::Buffer(size_t length) {
    allocate(length);
    _total_offset = 0;
}

Buffer::~Buffer() { deallocate(); }

Buffer::Buffer(Buffer* parent, size_t offset, size_t length) {
    fromParent(parent, offset);
}

Buffer::Buffer(char* buffer, size_t length) {
    _data = new rawBuffer(buffer, length);
}

void Buffer::fromParent(const Buffer* parent, size_t offset, size_t length) {
    if (offset > parent->length()) {
        // Cannot create a sub-buffer with offset greater than the parent's
        // length
    }
    _total_offset = parent->_total_offset + offset;
    _data = parent->_data;
    _offset = offset;
    _clipLength = length;
}

void Buffer::allocate(size_t length) {
    if (_data) {
        deallocate();
    }
    _data = new rawBuffer(length);
}

void Buffer::deallocate() { _data = nullptr; }

void Buffer::fromBuffer(char* buffer, size_t length) {
    deallocate();
    _data = new rawBuffer(buffer, length);
}

Buffer Buffer::offset(size_t offset, size_t length) {
    Buffer buf;
    buf.fromParent(this, offset, length);
    return buf;
}

size_t Buffer::length() const {
    // Set the max length
    size_t len = _data->length() - _offset;
    // If a clip is defined and it is valid, use it
    if (_clipLength > 0 && _clipLength < len) {
        len = _clipLength;
    }
    return len;
}

size_t Buffer::getOffset() { return _offset; }

char* Buffer::toString() { return data(); }

string_t Buffer::toHex() {
    string_t output;
    /*stringstream output;
    char* start = data();
    for(size_t i = 0;i<length();i++) {
        output << hex << start[i] << " ";
    }
    return output.str();*/
    return output;
}

}  // namespace syndesi