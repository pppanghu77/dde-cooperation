//------------------------------------------------------------------------------
// Automatically generated by the Fast Binary Encoding compiler, do not modify!
// https://github.com/chronoxor/FastBinaryEncoding
// Source: FBE
// FBE version: 1.14.5.0
//------------------------------------------------------------------------------

#pragma once

#if defined(__clang__)
#pragma clang system_header
#elif defined(__GNUC__)
#pragma GCC system_header
#elif defined(_MSC_VER)
#pragma system_header
#endif

#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <cctype>
#include <future>
#include <iomanip>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <vector>

#if defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
#include <time.h>
#include <uuid/uuid.h>
#elif defined(_WIN32) || defined(_WIN64)
#undef DELETE
#undef ERROR
#undef Yield
#undef min
#undef max
#undef uuid_t
#endif

namespace FBE {

//! Bytes buffer type
/*!
    Represents bytes buffer which is a lightweight wrapper around std::vector<uint8_t>
    with similar interface.
*/
class buffer_t
{
public:
    typedef std::vector<uint8_t>::iterator iterator;
    typedef std::vector<uint8_t>::const_iterator const_iterator;
    typedef std::vector<uint8_t>::reverse_iterator reverse_iterator;
    typedef std::vector<uint8_t>::const_reverse_iterator const_reverse_iterator;

    buffer_t() = default;
    buffer_t(size_t capacity) { reserve(capacity); }
    buffer_t(const std::string& str) { assign(str); }
    buffer_t(size_t size, uint8_t value) { assign(size, value); }
    buffer_t(const uint8_t* data, size_t size) { assign(data, size); }
    buffer_t(const std::vector<uint8_t>& other) : _data(other) {}
    buffer_t(std::vector<uint8_t>&& other) : _data(std::move(other)) {}
    buffer_t(const buffer_t& other) = default;
    buffer_t(buffer_t&& other) = default;
    ~buffer_t() = default;

    buffer_t& operator=(const std::string& str) { assign(str); return *this; }
    buffer_t& operator=(const std::vector<uint8_t>& other) { _data = other; return *this; }
    buffer_t& operator=(std::vector<uint8_t>&& other) { _data = std::move(other); return *this; }
    buffer_t& operator=(const buffer_t& other) = default;
    buffer_t& operator=(buffer_t&& other) = default;

    uint8_t& operator[](size_t index) { return _data[index]; }
    const uint8_t& operator[](size_t index) const { return _data[index]; }

    bool empty() const { return _data.empty(); }
    size_t capacity() const { return _data.capacity(); }
    size_t size() const { return _data.size(); }
    size_t max_size() const { return _data.max_size(); }

    std::vector<uint8_t>& buffer() noexcept { return _data; }
    const std::vector<uint8_t>& buffer() const noexcept { return _data; }
    uint8_t* data() noexcept { return _data.data(); }
    const uint8_t* data() const noexcept { return _data.data(); }
    uint8_t& at(size_t index) { return _data.at(index); }
    const uint8_t& at(size_t index) const { return _data.at(index); }
    uint8_t& front() { return _data.front(); }
    const uint8_t& front() const { return _data.front(); }
    uint8_t& back() { return _data.back(); }
    const uint8_t& back() const { return _data.back(); }

    void reserve(size_t capacity) { _data.reserve(capacity); }
    void resize(size_t size, uint8_t value = 0) { _data.resize(size, value); }
    void shrink_to_fit() { _data.shrink_to_fit(); }

    void assign(const std::string& str) { assign((const uint8_t*)str.c_str(), str.size()); }
    void assign(const std::vector<uint8_t>& vec) { assign(vec.begin(), vec.end()); }
    void assign(size_t size, uint8_t value) { _data.assign(size, value); }
    void assign(const uint8_t* data, size_t size) { _data.assign(data, data + size); }
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) { _data.assign(first, last); }
    iterator insert(const_iterator position, uint8_t value) { return _data.insert(position, value); }
    iterator insert(const_iterator position, const std::string& str) { return insert(position, (const uint8_t*)str.c_str(), str.size()); }
    iterator insert(const_iterator position, const std::vector<uint8_t>& vec) { return insert(position, vec.begin(), vec.end()); }
    iterator insert(const_iterator position, size_t size, uint8_t value) { return _data.insert(position, size, value); }
    iterator insert(const_iterator position, const uint8_t* data, size_t size) { return _data.insert(position, data, data + size); }
    template <class InputIterator>
    iterator insert(const_iterator position, InputIterator first, InputIterator last) { return _data.insert(position, first, last); }
    iterator erase(const_iterator position) { return _data.erase(position); }
    iterator erase(const_iterator first, const_iterator last) { return _data.erase(first, last); }
    void clear() noexcept { _data.clear(); }

    void push_back(uint8_t value) { _data.push_back(value); }
    void pop_back() { _data.pop_back(); }

    template <class... Args>
    iterator emplace(const_iterator position, Args&&... args) { return _data.emplace(position, args...); }
    template <class... Args>
    void emplace_back(Args&&... args) { _data.emplace_back(args...); }

    iterator begin() noexcept { return _data.begin(); }
    const_iterator begin() const noexcept { return _data.begin(); }
    const_iterator cbegin() const noexcept { return _data.cbegin(); }
    reverse_iterator rbegin() noexcept { return _data.rbegin(); }
    const_reverse_iterator rbegin() const noexcept { return _data.rbegin(); }
    const_reverse_iterator crbegin() const noexcept { return _data.crbegin(); }
    iterator end() noexcept { return _data.end(); }
    const_iterator end() const noexcept { return _data.end(); }
    const_iterator cend() const noexcept { return _data.cend(); }
    reverse_iterator rend() noexcept { return _data.rend(); }
    const_reverse_iterator rend() const noexcept { return _data.rend(); }
    const_reverse_iterator crend() const noexcept { return _data.crend(); }

    //! Get the string equivalent from the bytes buffer
    std::string string() const { return std::string(_data.begin(), _data.end()); }

    //! Encode the Base64 string from the bytes buffer
    std::string base64encode() const;
    //! Decode the bytes buffer from the Base64 string
    static buffer_t base64decode(const std::string& str);

    //! Swap two instances
    void swap(buffer_t& value) noexcept
    { using std::swap; swap(_data, value._data); }
    friend void swap(buffer_t& value1, buffer_t& value2) noexcept
    { value1.swap(value2); }

private:
    std::vector<uint8_t> _data;
};

//! Decimal type
/*!
    Represents decimal type using double and provides basic arithmetic operations.
*/
class decimal_t
{
public:
    decimal_t() noexcept { _value = 0.0; }
    decimal_t(int8_t value) noexcept { _value = (double)value; }
    decimal_t(uint8_t value) noexcept { _value = (double)value; }
    decimal_t(int16_t value) noexcept { _value = (double)value; }
    decimal_t(uint16_t value) noexcept { _value = (double)value; }
    decimal_t(int32_t value) noexcept { _value = (double)value; }
    decimal_t(uint32_t value) noexcept { _value = (double)value; }
    decimal_t(int64_t value) noexcept { _value = (double)value; }
    decimal_t(uint64_t value) noexcept { _value = (double)value; }
    decimal_t(float value) noexcept { _value = (double)value; }
    decimal_t(double value) noexcept { _value = value; }
    template <typename T>
    explicit decimal_t(const T& value) noexcept { _value = (double)value; }
    decimal_t(const decimal_t& value) noexcept = default;
    decimal_t(decimal_t&& value) noexcept = default;
    ~decimal_t() noexcept = default;

    template <typename T>
    decimal_t& operator=(const T& value) noexcept { _value = (double)value; return *this; }
    decimal_t& operator=(const decimal_t& value) noexcept = default;
    decimal_t& operator=(decimal_t&& value) noexcept = default;

    // Arithmetic operators
    decimal_t operator+() const noexcept { return decimal_t(_value); }
    decimal_t operator-() const noexcept { return decimal_t(-_value); }

    decimal_t& operator++() noexcept { return *this += 1; }
    decimal_t operator++(int) noexcept { decimal_t temp(*this); ++*this; return temp; }
    decimal_t& operator--() noexcept { return *this -= 1; }
    decimal_t operator--(int) noexcept { decimal_t temp(*this); --*this; return temp; }

    decimal_t& operator+=(const decimal_t& value) noexcept { return *this = *this + value; }
    decimal_t& operator-=(const decimal_t& value) noexcept { return *this = *this - value; }
    decimal_t& operator*=(const decimal_t& value) noexcept { return *this = *this * value; }
    decimal_t& operator/=(const decimal_t& value) { return *this = *this / value; }

    template <typename T>
    decimal_t& operator+=(const T& value) noexcept { return *this = *this + decimal_t(value); }
    template <typename T>
    decimal_t& operator-=(const T& value) noexcept { return *this = *this - decimal_t(value); }
    template <typename T>
    decimal_t& operator*=(const T& value) noexcept { return *this = *this * decimal_t(value); }
    template <typename T>
    decimal_t& operator/=(const T& value) { return *this = *this / decimal_t(value); }

    template <typename T>
    friend T& operator+=(T& value1, const decimal_t& value2) noexcept { return value1 = (T)(decimal_t(value1) + value2); }
    template <typename T>
    friend T& operator-=(T& value1, const decimal_t& value2) noexcept { return value1 = (T)(decimal_t(value1) - value2); }
    template <typename T>
    friend T& operator*=(T& value1, const decimal_t& value2) noexcept { return value1 = (T)(decimal_t(value1) * value2); }
    template <typename T>
    friend T& operator/=(T& value1, const decimal_t& value2) { return value1 = (T)(decimal_t(value1) / value2); }

    template <typename T>
    friend decimal_t operator+(const T& value1, const decimal_t& value2) noexcept { return decimal_t(value1) + value2; }
    template <typename T>
    friend decimal_t operator+(const decimal_t& value1, const T& value2) noexcept { return value1 + decimal_t(value2); }
    friend decimal_t operator+(const decimal_t& value1, const decimal_t& value2) noexcept { return decimal_t(value1._value + value2._value); }

    template <typename T>
    friend decimal_t operator-(const T& value1, const decimal_t& value2) noexcept { return decimal_t(value1) - value2; }
    template <typename T>
    friend decimal_t operator-(const decimal_t& value1, const T& value2) noexcept { return value1 - decimal_t(value2); }
    friend decimal_t operator-(const decimal_t& value1, const decimal_t& value2) noexcept { return decimal_t(value1._value - value2._value); }

    template <typename T>
    friend decimal_t operator*(const T& value1, const decimal_t& value2) noexcept { return decimal_t(value1) * value2; }
    template <typename T>
    friend decimal_t operator*(const decimal_t& value1, const T& value2) noexcept { return value1 * decimal_t(value2); }
    friend decimal_t operator*(const decimal_t& value1, const decimal_t& value2) noexcept { return decimal_t(value1._value * value2._value); }

    template <typename T>
    friend decimal_t operator/(const T& value1, const decimal_t& value2) { return decimal_t(value1) / value2; }
    template <typename T>
    friend decimal_t operator/(const decimal_t& value1, const T& value2) { return value1 / decimal_t(value2); }
    friend decimal_t operator/(const decimal_t& value1, const decimal_t& value2) { return decimal_t(value1._value / value2._value); }

    // Comparison operators
    template <typename T>
    friend bool operator==(const T& value1, const decimal_t& value2) noexcept { return decimal_t(value1) == value2; }
    template <typename T>
    friend bool operator==(const decimal_t& value1, const T& value2) noexcept { return value1 == decimal_t(value2); }
    friend bool operator==(const decimal_t& value1, const decimal_t& value2) noexcept { return value1._value == value2._value; }

    template <typename T>
    friend bool operator!=(const T& value1, const decimal_t& value2) noexcept { return decimal_t(value1) != value2; }
    template <typename T>
    friend bool operator!=(const decimal_t& value1, const T& value2) noexcept { return value1 != decimal_t(value2); }
    friend bool operator!=(const decimal_t& value1, const decimal_t& value2) noexcept { return value1._value != value2._value; }

    template <typename T>
    friend bool operator<(const T& value1, const decimal_t& value2) noexcept { return decimal_t(value1) < value2; }
    template <typename T>
    friend bool operator<(const decimal_t& value1, const T& value2) noexcept { return value1 < decimal_t(value2); }
    friend bool operator<(const decimal_t& value1, const decimal_t& value2) noexcept { return value1._value < value2._value; }

    template <typename T>
    friend bool operator>(const T& value1, const decimal_t& value2) noexcept { return decimal_t(value1) > value2; }
    template <typename T>
    friend bool operator>(const decimal_t& value1, const T& value2) noexcept { return value1 > decimal_t(value2); }
    friend bool operator>(const decimal_t& value1, const decimal_t& value2) noexcept { return value1._value > value2._value; }

    template <typename T>
    friend bool operator<=(const T& value1, const decimal_t& value2) noexcept { return decimal_t(value1) <= value2; }
    template <typename T>
    friend bool operator<=(const decimal_t& value1, const T& value2) noexcept { return value1 <= decimal_t(value2); }
    friend bool operator<=(const decimal_t& value1, const decimal_t& value2) noexcept { return value1._value <= value2._value; }

    template <typename T>
    friend bool operator>=(const T& value1, const decimal_t& value2) noexcept { return decimal_t(value1) >= value2; }
    template <typename T>
    friend bool operator>=(const decimal_t& value1, const T& value2) noexcept { return value1 >= decimal_t(value2); }
    friend bool operator>=(const decimal_t& value1, const decimal_t& value2) noexcept { return value1._value >= value2._value; }

    // Type cast
    operator bool() const noexcept { return (_value != 0.0); }
    operator uint8_t() const noexcept { return (uint8_t)_value; }
    operator uint16_t() const noexcept { return (uint16_t)_value; }
    operator uint32_t() const noexcept { return (uint32_t)_value; }
    operator uint64_t() const noexcept { return (uint64_t)_value; }
    operator float() const noexcept { return (float)_value; }
    operator double() const noexcept { return (double)_value; }

    //! Get string from the current decimal value
    std::string string() const { return std::to_string(_value); }

    //! Input instance from the given input stream
    friend std::istream& operator>>(std::istream& is, decimal_t& value)
    { is >> value._value; return is; }
    //! Output instance into the given output stream
    friend std::ostream& operator<<(std::ostream& os, const decimal_t& value)
    { os << value.string(); return os; }

#if defined(LOGGING_PROTOCOL)
    //! Store logging format
    friend CppLogging::Record& operator<<(CppLogging::Record& record, const decimal_t& value)
    { return record.StoreCustom(value._value); }
#endif

    //! Swap two instances
    void swap(decimal_t& value) noexcept
    { using std::swap; swap(_value, value._value); }
    friend void swap(decimal_t& value1, decimal_t& value2) noexcept
    { value1.swap(value2); }

private:
    double _value;
};

} // namespace FBE

#if defined(FMT_VERSION) && (FMT_VERSION >= 90000)
template <>
struct fmt::formatter<FBE::decimal_t> : formatter<std::string_view>
{
    template <typename FormatContext>
    auto format(const FBE::decimal_t& value, FormatContext& ctx) const
    {
        return formatter<string_view>::format((double)value, ctx);
    }
};
#endif

template <>
struct std::hash<FBE::decimal_t>
{
    typedef FBE::decimal_t argument_type;
    typedef size_t result_type;

    result_type operator() (const argument_type& value) const
    {
        result_type result = 17;
        result = result * 31 + std::hash<double>()((double)value);
        return result;
    }
};

namespace FBE {

// Register a new enum-based flags macro
#define FBE_ENUM_FLAGS(type)\
inline FBE::Flags<type> operator|(type f1, type f2) noexcept { return FBE::Flags<type>(f1) | FBE::Flags<type>(f2); }\
inline FBE::Flags<type> operator&(type f1, type f2) noexcept { return FBE::Flags<type>(f1) & FBE::Flags<type>(f2); }\
inline FBE::Flags<type> operator^(type f1, type f2) noexcept { return FBE::Flags<type>(f1) ^ FBE::Flags<type>(f2); }

// Enum-based flags
template <typename TEnum>
class Flags
{
    // Enum underlying type
    typedef typename std::make_unsigned<typename std::underlying_type<TEnum>::type>::type type;

public:
    Flags() noexcept : _value(0) {}
    explicit Flags(type value) noexcept : _value(value) {}
    explicit Flags(TEnum value) noexcept : _value((type)value) {}
    Flags(const Flags&) noexcept = default;
    Flags(Flags&&) noexcept = default;
    ~Flags() noexcept = default;

    Flags& operator=(type value) noexcept
    { _value = value; return *this; }
    Flags& operator=(TEnum value) noexcept
    { _value = (type)value; return *this; }
    Flags& operator=(const Flags&) noexcept = default;
    Flags& operator=(Flags&&) noexcept = default;

    // Is any flag set?
    explicit operator bool() const noexcept { return isset(); }

    // Is no flag set?
    bool operator!() const noexcept { return !isset(); }

    // Reverse all flags
    Flags operator~() const noexcept { return Flags(~_value); }

    // Flags logical assign operators
    Flags& operator&=(const Flags& flags) noexcept
    { _value &= flags._value; return *this; }
    Flags& operator|=(const Flags& flags) noexcept
    { _value |= flags._value; return *this; }
    Flags& operator^=(const Flags& flags) noexcept
    { _value ^= flags._value; return *this; }

    // Flags logical friend operators
    friend Flags operator&(const Flags& flags1, const Flags& flags2) noexcept
    { return Flags(flags1._value & flags2._value); }
    friend Flags operator|(const Flags& flags1, const Flags& flags2) noexcept
    { return Flags(flags1._value | flags2._value); }
    friend Flags operator^(const Flags& flags1, const Flags& flags2) noexcept
    { return Flags(flags1._value ^ flags2._value); }

    // Flags comparison
    friend bool operator==(const Flags& flags1, const Flags& flags2) noexcept
    { return flags1._value == flags2._value; }
    friend bool operator!=(const Flags& flags1, const Flags& flags2) noexcept
    { return flags1._value != flags2._value; }

    // Convert to the enum value
    operator TEnum() const noexcept { return (TEnum)_value; }

    //! Is any flag set?
    bool isset() const noexcept { return (_value != 0); }
    //! Is the given flag set?
    bool isset(type value) const noexcept { return (_value & value) != 0; }
    //! Is the given flag set?
    bool isset(TEnum value) const noexcept { return (_value & (type)value) != 0; }

    // Get the enum value
    TEnum value() const noexcept { return (TEnum)_value; }
    // Get the underlying enum value
    type underlying() const noexcept { return _value; }
    // Get the bitset value
    std::bitset<sizeof(type) * 8> bitset() const noexcept { return {_value}; }

    // Swap two instances
    void swap(Flags& flags) noexcept { using std::swap; swap(_value, flags._value); }
    template <typename UEnum>
    friend void swap(Flags<UEnum>& flags1, Flags<UEnum>& flags2) noexcept;

private:
    type _value;
};

template <typename TEnum>
inline void swap(Flags<TEnum>& flags1, Flags<TEnum>& flags2) noexcept
{
    flags1.swap(flags2);
}

// Get Epoch timestamp
inline uint64_t epoch() { return 0ull; }
// Get UTC timestamp
uint64_t utc();

//! Universally unique identifier (UUID)
/*!
    A universally unique identifier (UUID) is an identifier standard used
    in software construction. This implementation generates the following
    UUID types:
    - Nil UUID0 (all bits set to zero)
    - Sequential UUID1 (time based version)
    - Random UUID4 (randomly or pseudo-randomly generated version)

    A UUID is simply a 128-bit value: "123e4567-e89b-12d3-a456-426655440000"

    https://en.wikipedia.org/wiki/Universally_unique_identifier
    https://www.ietf.org/rfc/rfc4122.txt
*/
class uuid_t
{
public:
    //! Default constructor
    uuid_t() : _data() { _data.fill(0); }
    //! Initialize UUID with a given string
    /*!
        \param uuid - UUID string
    */
    explicit uuid_t(const std::string& uuid);
    //! Initialize UUID with a given 16 bytes data buffer
    /*!
        \param data - UUID 16 bytes data buffer
    */
    explicit uuid_t(const std::array<uint8_t, 16>& data) : _data(data) {}
    uuid_t(const uuid_t&) = default;
    uuid_t(uuid_t&&) noexcept = default;
    ~uuid_t() = default;

    uuid_t& operator=(const std::string& uuid)
    { _data = uuid_t(uuid).data(); return *this; }
    uuid_t& operator=(const std::array<uint8_t, 16>& data)
    { _data = data; return *this; }
    uuid_t& operator=(const uuid_t&) = default;
    uuid_t& operator=(uuid_t&&) noexcept = default;

    // UUID comparison
    friend bool operator==(const uuid_t& uuid1, const uuid_t& uuid2)
    { return uuid1._data == uuid2._data; }
    friend bool operator!=(const uuid_t& uuid1, const uuid_t& uuid2)
    { return uuid1._data != uuid2._data; }
    friend bool operator<(const uuid_t& uuid1, const uuid_t& uuid2)
    { return uuid1._data < uuid2._data; }
    friend bool operator>(const uuid_t& uuid1, const uuid_t& uuid2)
    { return uuid1._data > uuid2._data; }
    friend bool operator<=(const uuid_t& uuid1, const uuid_t& uuid2)
    { return uuid1._data <= uuid2._data; }
    friend bool operator>=(const uuid_t& uuid1, const uuid_t& uuid2)
    { return uuid1._data >= uuid2._data; }

    //! Check if the UUID is nil UUID0 (all bits set to zero)
    explicit operator bool() const noexcept { return *this != nil(); }

    //! Get the UUID data buffer
    std::array<uint8_t, 16>& data() noexcept { return _data; }
    //! Get the UUID data buffer
    const std::array<uint8_t, 16>& data() const noexcept { return _data; }

    //! Get string from the current UUID in format "00000000-0000-0000-0000-000000000000"
    std::string string() const;

    //! Generate nil UUID0 (all bits set to zero)
    static uuid_t nil() { return uuid_t(); }
    //! Generate sequential UUID1 (time based version)
    static uuid_t sequential();
    //! Generate random UUID4 (randomly or pseudo-randomly generated version)
    static uuid_t random();

    //! Output instance into the given output stream
    friend std::ostream& operator<<(std::ostream& os, const uuid_t& uuid)
    { os << uuid.string(); return os; }

#if defined(LOGGING_PROTOCOL)
    //! Store logging format
    friend CppLogging::Record& operator<<(CppLogging::Record& record, const uuid_t& uuid);
#endif

    //! Swap two instances
    void swap(uuid_t& uuid) noexcept
    { using std::swap; swap(_data, uuid._data); }
    friend void swap(uuid_t& uuid1, uuid_t& uuid2) noexcept
    { uuid1.swap(uuid2); }

private:
    std::array<uint8_t, 16> _data;
};

} // namespace FBE

#if defined(FMT_VERSION) && (FMT_VERSION >= 90000)
template <>
struct fmt::formatter<FBE::uuid_t> : formatter<std::string_view>
{
    template <typename FormatContext>
    auto format(const FBE::uuid_t& value, FormatContext& ctx) const
    {
        return formatter<string_view>::format(value.string(), ctx);
    }
};
#endif

template <>
struct std::hash<FBE::uuid_t>
{
    typedef FBE::uuid_t argument_type;
    typedef size_t result_type;

    result_type operator() (const argument_type& value) const
    {
        result_type result = 17;
        std::hash<uint8_t> hasher;
        for (size_t i = 0; i < value.data().size(); ++i)
            result = result * 31 + hasher(value.data()[i]);
        return result;
    }
};

namespace FBE {

// Fast Binary Encoding buffer based on the dynamic byte buffer
class FBEBuffer
{
public:
    FBEBuffer() : _data(nullptr), _capacity(0), _size(0), _offset(0) {}
    // Initialize the read buffer with the given byte buffer and offset
    explicit FBEBuffer(const void* data, size_t size, size_t offset = 0) { attach(data, size, offset); }
    // Initialize the read buffer with the given byte vector and offset
    explicit FBEBuffer(const std::vector<uint8_t>& buffer, size_t offset = 0) { attach(buffer, offset); }
    // Initialize the read buffer with another buffer and offset
    explicit FBEBuffer(const FBEBuffer& buffer, size_t offset = 0) { attach(buffer.data(), buffer.size(), offset); }
    // Initialize the write buffer with the given capacity
    explicit FBEBuffer(size_t capacity) : FBEBuffer() { reserve(capacity); }
    FBEBuffer(const FBEBuffer&) = delete;
    FBEBuffer(FBEBuffer&&) noexcept = delete;
    ~FBEBuffer() { if (_capacity > 0) std::free(_data); }

    FBEBuffer& operator=(const FBEBuffer&) = delete;
    FBEBuffer& operator=(FBEBuffer&&) noexcept = delete;

    bool empty() const noexcept { return (_data == nullptr) || (_size == 0); }
    const uint8_t* data() const noexcept { return _data; }
    uint8_t* data() noexcept { return _data; }
    size_t capacity() const noexcept { return _capacity; }
    size_t size() const noexcept { return _size; }
    size_t offset() const noexcept { return _offset; }

    // Attach the given buffer with a given offset to the current read buffer
    void attach(const void* data, size_t size, size_t offset = 0);
    // Attach the given byte vector with a given offset to the current read buffer
    void attach(const std::vector<uint8_t>& buffer, size_t offset = 0);

    // Clone the given buffer with a given offset to the current buffer
    void clone(const void* data, size_t size, size_t offset = 0);
    // Clone the given vector with a given offset to the current buffer
    void clone(const std::vector<uint8_t>& buffer, size_t offset = 0);

    // Allocate memory in the current write buffer and return offset to the allocated memory block
    size_t allocate(size_t size);
    // Remove some memory of the given size from the current write buffer
    void remove(size_t offset, size_t size);
    // Reserve memory of the given capacity in the current write buffer
    void reserve(size_t capacity);
    // Resize the current write buffer
    void resize(size_t size);
    // Reset the current write buffer and its offset
    void reset();

    // Shift the current write buffer offset
    void shift(size_t offset) { _offset += offset; }
    // Unshift the current write buffer offset
    void unshift(size_t offset) { _offset -= offset; }

private:
    uint8_t* _data;
    size_t _capacity;
    size_t _size;
    size_t _offset;
};

// Fast Binary Encoding base model
class Model
{
public:
    Model() : Model(nullptr) {}
    Model(const std::shared_ptr<FBEBuffer>& buffer) { _buffer = buffer ? buffer : std::make_shared<FBEBuffer>(); }
    Model(const Model&) = default;
    Model(Model&&) noexcept = default;
    ~Model() = default;

    Model& operator=(const Model&) = default;
    Model& operator=(Model&&) noexcept = default;

    // Get the model buffer
    FBEBuffer& buffer() noexcept { return *_buffer; }
    const FBEBuffer& buffer() const noexcept { return *_buffer; }

    // Attach the model buffer
    void attach(const void* data, size_t size, size_t offset = 0) { _buffer->attach(data, size, offset); }
    void attach(const std::vector<uint8_t>& buffer, size_t offset = 0) { _buffer->attach(buffer, offset); }
    void attach(const FBEBuffer& buffer, size_t offset = 0) { _buffer->attach(buffer.data(), buffer.size(), offset); }

    // Model buffer operations
    size_t allocate(size_t size) { return _buffer->allocate(size); }
    void remove(size_t offset, size_t size) { _buffer->remove(offset, size); }
    void reserve(size_t capacity) { _buffer->reserve(capacity); }
    void resize(size_t size) { _buffer->resize(size); }
    void reset() { _buffer->reset(); }
    void shift(size_t offset) { _buffer->shift(offset); }
    void unshift(size_t offset) { _buffer->unshift(offset); }

private:
    std::shared_ptr<FBEBuffer> _buffer;
};

} // namespace FBE
