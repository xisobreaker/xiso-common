#include "xiso/common/strutils.h"

namespace xiso {
namespace common {

std::string str_trim(const std::string &msg, const char ch)
{
    std::string message = msg;
    while (message.length() > 0) {
        if (message[0] != ch) {
            break;
        }
        message.erase(0, 1);
    }

    while (message.length() > 0) {
        if (message[message.length() - 1] != ch)
            break;
        message.erase(message.length() - 1, message.length());
    }
    return message;
}

std::string str_replace(const std::string &msg, std::string src, std::string dst)
{
    std::string message = msg;
    while (message.find(src) != std::string::npos) {
        message.replace(message.find(src), src.length(), dst);
    }
    return message;
}

bool str_startswith(const std::string &str, std::string start)
{
    auto startLen = start.length();
    if (str.length() >= startLen) {
        std::string temp = str.substr(0, startLen);
        return temp.compare(start) == 0;
    }
    return false;
}

bool str_endswith(const std::string &str, std::string end)
{
    auto endLen = end.length();
    if (str.length() >= endLen) {
        std::string temp = str.substr(str.length() - endLen, str.length());
        return temp.compare(end) == 0;
    }
    return false;
}

} // namespace common
} // namespace xiso