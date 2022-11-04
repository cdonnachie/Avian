// Copyright (c) 2022 The Avian Core developers
// Copyright (c) 2022 Shafil Alam
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AVIAN_NAME_SYSTEM_H
#define AVIAN_NAME_SYSTEM_H

#include <string>
#include <array>

#include "univalue.h"

/** Avian Name System */
class CAvianNameSystem {
public:  

    /** Static prefix for ANS IDs */
    static const std::string prefix;
    /** Static domain */
    static const std::string domain;

    /** ANS types */
    enum Type {
        ADDR = 0x0,
        IP = 0x1
    };

    CAvianNameSystem(Type type, std::string rawData);
    CAvianNameSystem(std::string ansID);

    /** Get ANS ID as string */
    std::string to_string();
    /** Get JSON object about this ANS ID */
    UniValue to_object();

    /** ANS return types */
    Type type() { return m_type; };
    std::string addr() { return m_addr; };
    std::string ip() { return m_ip; };

    /** Check if valid IPv4 address */
    static bool CheckIP(std::string rawip, bool isHex);

    /** Check if valid ANS ID */
    static bool IsValidID(std::string ansID);

    /** Check ANS raw data based on type */
    static bool CheckTypeData(Type type, std::string typeData);
    /** Convert raw data into ANS ID type data */
    static std::string FormatTypeData(Type type, std::string typeData, std::string& error);

    /** Convert ANS type into string with description */
    static std::pair<std::string, std::string> enum_to_string(Type type) {
        switch(type) {
            case ADDR:
                return std::make_pair("Avian address", "Enter an Avian address");
            case IP:
                return std::make_pair("IP [DNS A record]", "Enter IP address");
            default:
                return std::make_pair("Invalid", "Invalid");
        }
    }

private:
    /** ANS types as private */
    Type m_type;
    std::string m_addr;
    std::string m_ip;
};

/** Public array of ANS types  */
constexpr std::array<CAvianNameSystem::Type, 2> ANSTypes { 
    CAvianNameSystem::ADDR, 
    CAvianNameSystem::IP
};

#endif // AVIAN_NAME_SYSTEM_H
