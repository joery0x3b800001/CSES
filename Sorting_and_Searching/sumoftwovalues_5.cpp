#include <algorithm>
#include <array>
#include <bit>
#include <charconv>
#include <complex>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <functional>
#include <limits>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
// contest/io.hpp
 
 
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
        static constexpr size_t NUM_CHARS = 64;
 
        static constexpr char LAST_WHITESPACE = ' ';
 
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
 
        template <std::integral Num>
        auto readInt(Num& num) -> bool {
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
            constexpr char DIGIT_MASK = 0x0f;
            num = *head_ & DIGIT_MASK;
            while (*++head_ > LAST_WHITESPACE) {
                num = BASE * num + (*head_ & DIGIT_MASK);
            }
 
            if (sign) {
                num = -num;
            }
 
            return true;
        }
 
        template <std::floating_point Real>
        auto readFloat(Real& real) -> bool {
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
 
        auto readString(std::string& s, char delim = LAST_WHITESPACE) -> bool {
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
 
        template <typename T>
        auto read(T& var) -> bool {
            *this >> var;
            return true;
        }
 
        template <typename T, typename... Ts>
        auto read(T& x, Ts&&... xs) -> bool {
            return read(x)
                 ? read(std::forward<Ts>(xs)...)
                 : false;
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
 
    template <std::integral Num>
    auto operator>>(Scanner& scanner, Num& num) -> Scanner& {
        scanner.readInt(num);
        return scanner;
    }
 
    template <std::floating_point Real>
    auto operator>>(Scanner& scanner, Real& real) -> Scanner& {
        scanner.readFloat(real);
        return scanner;
    }
 
    auto operator>>(Scanner& scanner, std::string& s) -> Scanner& {
        scanner.readString(s);
        return scanner;
    }
 
    template <typename A, typename B>
    auto operator>>(Scanner& scanner, std::pair<A, B>& pair) -> Scanner& {
        scanner.read(pair.first);
        scanner.read(pair.second);
 
        return scanner;
    }
 
    template <typename... Ts>
    auto operator>>(Scanner& scanner, std::tuple<Ts...>& tuple) -> Scanner& {
        std::apply(
            [&scanner](Ts&... args) {
                ((scanner >> args), ...);
            }, tuple
        );
        return scanner;
    }
 
    template <typename C, typename V=decltype(*std::begin(std::declval<C>()))>
    auto operator>>(Scanner& scanner, C& c) -> std::enable_if_t<!std::is_same_v<std::remove_cvref<V>, char>, Scanner&> {
        for (auto& v : c) {
            scanner >> v;
        }
 
        return scanner;
    }
 
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
 
        inline auto writeDelim() -> void {
            writeSingle(delim_);
        }
 
        template <std::integral Num>
        auto writeInt(Num num) -> void {
            if constexpr (std::is_signed_v<Num>) {
                if (num < 0) {
                    writeSingle('-');
                    num = -num;
                }
            }
 
            static std::array<char, 32> buf;
            auto written = 0u;
            while (num >= Num{100}) {
                const auto& digits = LOOKUP_TWO[num % 100];
                buf[written++] = digits[0];
                buf[written++] = digits[1];
                num /= Num{100};
            }
            if (num >= Num{10}) {
                const auto& digits = LOOKUP_TWO[num];
                buf[written++] = digits[0];
                buf[written++] = digits[1];
            } else {
                buf[written++] = static_cast<char>('0' + num);
            }
 
            std::reverse(buf.begin(), buf.begin() + written);
            if (tail_ + NUM_CHARS > mainBuf_ + BUF_SIZE) [[unlikely]] {
                flush();
            }
 
            std::memcpy(tail_, buf.begin(), written);
            tail_ += written;
        }
 
        template <std::floating_point Real>
        auto writeFloat(Real real) -> void {
            if (tail_ + NUM_CHARS > mainBuf_ + BUF_SIZE) [[unlikely]] {
                flush();
            }
 
            // TODO: customize number of digits
            // TODO: from_chars
            tail_ += std::snprintf(tail_, BUF_SIZE, "%.20lf", real);
        }
 
        auto writeString(std::string_view sv) -> void {
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
 
        template <typename T, typename... Ts>
        auto write(T&& t, Ts&&... ts) -> void {
            *this << std::forward<T>(t);
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
 
    template <std::integral Num>
    auto operator<<(Writer& writer, const Num& num) -> Writer& {
        writer.writeInt(num);
        return writer;
    }
 
    template <std::floating_point Real>
    auto operator<<(Writer& writer, const Real& real) -> Writer& {
        writer.writeFloat(real);
        return writer;
    }
 
    auto operator<<(Writer& writer, char c) -> Writer& {
        writer.writeSingle(c);
        return writer;
    }
 
    auto operator<<(Writer& writer, std::string_view s) -> Writer& {
        writer.writeString(s);
        return writer;
    }
 
    template <std::floating_point Real>
    auto operator<<(Writer& writer, const std::complex<Real>& complex) -> Writer& {
        writer.write(complex.real, complex.imag);
        return writer;
    }
 
    template <typename A, typename B>
    auto operator<<(Writer& writer, const std::pair<A, B>& pair) -> Writer& {
        writer.write(pair.first, pair.second);
        return writer;
    }
 
    template <typename C, typename V=decltype(*std::begin(std::declval<C>()))>
    auto operator<<(Writer& writer, const C& c) -> std::enable_if_t<!std::is_same_v<std::remove_cvref_t<V>, char>, Writer&> {
        bool first = true;
        for (const auto& v : c) {
            if (!first) {
                writer.writeDelim();
            } else {
                first = false;
            }
 
            writer.write(v);
        }
 
        return writer;
    }
 
    template <typename... Ts>
    auto operator<<(Writer& writer, const std::tuple<Ts...>& tuple) -> Writer& {
        std::apply(
            [&writer](const Ts&... args) {
                writer.write(args...);
            }, tuple
        );
        return writer;
    }
} // namespace ble
 
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
 
// contest/util.hpp
 
 
namespace ble {
 
template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T&& fun): fun_(std::forward<T>(fun)) {}
 
    template<class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
 
template<class Fun>
decltype(auto) YC(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
 
template <typename T>
constexpr auto setmin(T& a, const T& b) -> T& {
    return a = std::min(a, b);
}
 
template <typename T>
constexpr auto setmax(T& a, const T& b) -> T&{
    return a = std::max(a, b);
}
 
template <typename T>
constexpr auto nextPow2(T x) -> T {
    if (x == 0) {
        return 1;
    } else if (x & (x - 1)) {
        return T{1} << (T{std::numeric_limits<T>::digits} - std::countl_zero(x));
    } else {
        return x;
    }
}
 
} // namespace ble
 
// 1640.cpp
 
ble::Scanner scan;
ble::Writer writer;
 
int main() {
    i32 n;
    i64 x;
    scan.read(n, x);
 
    Vec<i64> a(n);
    scan.read(a);
 
    Vec<i64> b(a);
    std::sort(b.begin(), b.end());
 
    i32 s = 0, e = n - 1;
    i64 cur = b[s] + b[e];
    while ((s < e) & (cur != x)) {
        if (cur > x) {
            --e;
        } else {
            ++s;
        }
 
        cur = b[s] + b[e];
    }
 
    if ((s >= e) | (cur != x)) {
        writer.writeln("IMPOSSIBLE");
        return 0;
    }
 
    auto it1 = std::find(a.begin(), a.end(), b[s]);
    auto it2 = std::find(b[s] == b[e] ? it1 + 1 : a.begin(), a.end(), b[e]);
 
    writer.writeln(it1 - a.begin() + 1, it2 - a.begin() + 1);
 
    return 0;
}