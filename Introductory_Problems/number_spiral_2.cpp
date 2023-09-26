#include <array>
#include <charconv>
#include <complex>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
// contest/io.h
 
 
namespace ble {
    namespace detail {
        constexpr auto makeLookupTwo() -> std::array<std::array<char, 2>, 100> {
            std::array<std::array<char, 2>, 100> res;
            // Note these are stored in reverse order because we build the integer in reverse.
            for (auto i = 0; i < 100; ++i) {
                res[i][0] = '0' + (i % 10);
                res[i][1] = '0' + (i / 10);
            }
 
            return res;
        }
    }
 
    class Scanner {
    private:
        static constexpr size_t BUF_SIZE = 1 << 16;
        // Much bigger than needed to be safe.
        static constexpr size_t NUM_CHARS = 64;
 
    public:
        Scanner(): head_(mainBuf_), tail_(mainBuf_), input_(stdin) {}
 
        inline auto isEmpty() const -> bool {
            return head_ == tail_;
        }
 
        auto fillBuf() -> bool {
            auto rem = tail_ - head_;
            if (rem > 0) {
                // can't use memcpy here because buf can be very small.
                std::memmove(mainBuf_, head_, rem);
            }
            char* readStart = mainBuf_ + rem;
            auto bytesRead = std::fread(readStart, sizeof(char), BUF_SIZE - rem, input_);
            tail_ = readStart + bytesRead;
            head_ = mainBuf_;
 
            return bytesRead > 0;
        }
 
        // advance until non-empty and pointing to non-whitespace.
        auto skipWhitespace(char last=LAST_WHITESPACE) -> void {
            while (isEmpty() || *head_ <= last) {
                if (isEmpty()) [[unlikely]] {
                    fillBuf();
                } else {
                    ++head_;
                }
            }
        }
 
        // Try to ensure we have at least TOKEN_SIZE chars left.
        template <size_t TOKEN_SIZE = NUM_CHARS>
        auto ensureToken(char last=LAST_WHITESPACE) -> bool {
            bool valid = true;
            static_assert(BUF_SIZE > 2 * TOKEN_SIZE, "Should only need at most one re-read.");
            skipWhitespace(last);
 
            // only have to do this once due to the above assert
            auto curSize = static_cast<size_t>(tail_ - head_);
            if (curSize < TOKEN_SIZE) [[unlikely]] {
                bool didFill = fillBuf();
                if (!didFill && curSize == 0) [[unlikely]] {
                    return false;
                }
 
                skipWhitespace(last);
            }
 
            return valid;
        }
 
        static constexpr char LAST_WHITESPACE = ' ';
 
        template <std::integral Num>
        auto read(Num& num) -> bool {
            if (!ensureToken()) [[unlikely]] {
                return false;
            }
 
            bool sign = false;
            if constexpr (std::is_signed_v<Num>) {
                if (*head_ == '-') {
                    sign = true;
                    ++head_;
                }
            }
 
            constexpr Num BASE{10};
            num = *head_ & 0x0f;
            while (*++head_ > LAST_WHITESPACE) {
                num = BASE * num + (*head_ & 0x0f);
            }
 
            if (sign) {
                num = -num;
            }
 
            return true;
        }
 
        template <std::floating_point Real>
        auto read(Real& real) -> bool {
            if (!ensureToken()) [[unlikely]] {
                return false;
            }
 
#if __cpp_lib_to_chars >= 201611L
            auto [ptr, ec] = std::from_chars(head_, tail_, real);
            head_ = ptr;
#else
            real = static_cast<Real>(std::strtod(head_, &head_));
#endif
 
            return true;
        }
 
        auto read(std::string& s, char delim) -> bool {
            skipWhitespace(delim);
            s.clear();
 
            while (isEmpty() || *head_ > delim) {
                if (isEmpty()) {
                    fillBuf();
                } else {
                    s += *head_++;
                }
            }
 
            return !s.empty();
        }
 
        auto read(std::string& s) -> bool {
            return read(s, LAST_WHITESPACE);
        }
 
        template <std::floating_point Real>
        auto read(std::complex<Real>& complex) -> bool {
            Real real;
            Real imag;
            bool res = read(real, imag);
            if (!res) {
                return res;
            }
 
            complex.real(real);
            complex.imag(imag);
        }
 
        template <typename A, typename B>
        auto read(std::pair<A, B>& pair) -> bool {
            return read(pair.first, pair.second);
        }
 
        template <typename... Ts>
        auto read(std::tuple<Ts...>& tuple) -> bool {
            return std::apply([this](Ts&... args) -> bool { return ((read(args)), ...); }, tuple);
        }
 
        template <typename T, typename... Ts>
        auto read(T& x, Ts&&... xs) -> bool {
            return read(x)
                 ? read(std::forward<Ts>(xs)...)
                 : false;
        }
 
        template <typename C, typename V=decltype(*std::begin(std::declval<C>()))>
        auto read(C& c) -> std::enable_if_t<!std::is_same_v<std::remove_cvref<V>, char>, bool> {
            for (auto& v : c) {
                if (!read(v)) [[unlikely]] {
                    return false;
                }
            }
 
            return true;
        }
 
        auto read() -> bool {
            return true;
        }
 
    private:
        char mainBuf_[BUF_SIZE];
        char* head_;
        char* tail_;
        std::FILE * input_;
    };
 
    class Writer {
    private:
        static constexpr size_t BUF_SIZE = 1 << 16;
        static constexpr size_t NUM_CHARS = 64;
        static constexpr std::array<std::array<char, 2>, 100> LOOKUP_TWO = detail::makeLookupTwo();
 
    public:
        Writer(): tail_(mainBuf_), output_(stdout), delim_{' '} {}
        ~Writer() { flush(); std::fflush(output_); }
 
        auto setDelim(char delim) -> void {
            delim_ = delim;
        }
 
        auto flush() -> void {
            std::fwrite(mainBuf_, sizeof(char), tail_ - mainBuf_, output_);
            tail_ = mainBuf_;
        }
 
        auto writeSingle(char c) -> void {
            if (tail_ == mainBuf_ + BUF_SIZE) {
                flush();
            }
 
            *tail_++ = c;
        }
 
        auto writeDelim() -> void {
            writeSingle(delim_);
        }
 
        template <std::integral Int>
        auto writeSingle(Int num) -> void {
            if constexpr (std::is_signed_v<Int>) {
                if (num < 0) {
                    writeSingle('-');
                    num = -num;
                }
            }
 
            if (num < 10) {
                writeSingle(static_cast<char>(num + '0'));
                return;
            }
 
            static std::array<char, 32> buf;
            auto written = 0u;
            while (num >= Int{10}) {
                const auto& digits = LOOKUP_TWO[num % 100];
                buf[written++] = digits[0];
                buf[written++] = digits[1];
                num /= Int{100};
            }
            if (num > 0) {
                buf[written++] = static_cast<char>('0' + num);
            }
 
            std::reverse(buf.begin(), buf.begin() + written);
            if (tail_ + NUM_CHARS > mainBuf_ + BUF_SIZE) {
                flush();
            }
 
            std::memcpy(tail_, buf.begin(), written);
            tail_ += written;
        }
 
        template <std::floating_point Real>
        auto writeSingle(Real real) -> void {
            if (tail_ + NUM_CHARS > mainBuf_ + BUF_SIZE) {
                flush();
            }
 
            // TODO: customize number of digits
            tail_ += std::snprintf(tail_, BUF_SIZE, "%.20lf", real);
        }
 
        auto writeSingle(std::string_view sv) -> void {
            for (auto it = sv.begin(); it != sv.end();) {
                if (tail_ == mainBuf_ + BUF_SIZE) {
                    flush();
                }
 
                auto toWrite = std::min(mainBuf_ + BUF_SIZE - tail_, sv.end() - it);
                std::memcpy(tail_, it, toWrite);
                it += toWrite;
                tail_ += toWrite;
            }
        }
 
        template <std::floating_point Real>
        auto writeSingle(const std::complex<Real>& complex) -> void {
            write(complex.real, complex.imag);
        }
 
        template <typename A, typename B>
        auto writeSingle(const std::pair<A, B>& pair) -> void {
            write(pair.first, pair.second);
        }
 
        template <typename... Ts>
        auto writeSingle(const std::tuple<Ts...>& tuple) -> void {
            std::apply([this](const Ts&... args){ write(args...); }, tuple);
        }
 
        template <typename C, typename V=decltype(*std::begin(std::declval<C>()))>
        auto writeSingle(const C& c) -> std::enable_if_t<!std::is_same_v<std::remove_cvref_t<V>, char>> {
            bool first = true;
            for (const auto& v : c) {
                if (!first)
                    writeDelim();
 
                first = false;
 
                writeSingle(v);
            }
        }
 
        template <typename T, typename... Ts>
        auto write(T&& t, Ts&&... ts) -> void {
            writeSingle(std::forward<T>(t));
            if constexpr (sizeof...(Ts) > 0) {
                writeDelim();
                write(std::forward<Ts>(ts)...);
            }
        }
 
        template <typename... Ts>
        auto writeln(Ts&&... ts) -> void {
            write(std::forward<Ts>(ts)...);
            writeSingle('\n');
        }
 
    private:
        char mainBuf_[BUF_SIZE];
        char* tail_;
        std::FILE * output_;
        char delim_;
    };
}
 
// contest/types.h
 
template <typename T>
using Vec = std::vector<T>;
 
using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
 
using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
 
using f32 = float;
using f64 = double;
 
// 1071.cpp
 
int main() {
    ble::Scanner scan;
    ble::Writer writer;
 
    i32 t;
    scan.read(t);
    while (t-- > 0) {
        i64 x, y;
        scan.read(x, y);
 
        i64 band = std::max(x, y);
        i64 ans;
        if (band % 2 == 0) {
            if (x < y)
                ans = (band - 1) * (band - 1) + x;
            else
                ans = band * band + 1 - y;
        } else {
            if (x < y)
                ans = band * band + 1 - x;
            else
                ans = (band - 1) * (band - 1) + y;
        }
 
        writer.writeln(ans);
    }
 
    return 0;
}