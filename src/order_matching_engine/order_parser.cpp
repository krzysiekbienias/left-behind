#include "../utils/logger.hpp"
#include "order_matching_engine/parser_utils.hpp"
#include "../utils/string_utils.hpp"
#include "order_matching_engine/order_parser.hpp"

#include <sstream>
#include <stdexcept>

Command OrderParser::parseLineCsv(const std::string& line) const {
    std::stringstream ss(line);
    Command cmd;

    std::string tok;
    while (std::getline(ss, tok, ',')) {
        tok = string_utils::trim(tok);
        cmd.tokens.push_back(tok);
    }

    if (cmd.tokens.empty() || cmd.tokens[0].empty())
        throw std::invalid_argument("empty action");

    if (cmd.tokens[0].size() != 1)
        throw std::invalid_argument("invalid action token");

    const char action = cmd.tokens[0][0];

    auto requireN = [&](size_t n) {
        if (cmd.tokens.size() != n) throw std::invalid_argument("wrong field count");
    };

    // N / A => 8 pól(exact 8 chars)
    if (action == 'N' || action == 'A') {
        requireN(8);
        cmd.type = (action == 'N') ? CommandType::New : CommandType::Amend;

        cmd.rawOrder.action    = cmd.tokens[0];
        cmd.rawOrder.orderId   = cmd.tokens[1];
        cmd.rawOrder.timestamp = cmd.tokens[2];
        cmd.rawOrder.symbol    = cmd.tokens[3];
        cmd.rawOrder.orderType = cmd.tokens[4];
        cmd.rawOrder.side      = cmd.tokens[5];
        cmd.rawOrder.price     = cmd.tokens[6];
        cmd.rawOrder.quantity  = cmd.tokens[7];
        return cmd;
    }

    // X => Cancel: X,id,ts
    if (action == 'X') {
        requireN(3);
        cmd.type = CommandType::Cancel;
        cmd.orderId   = parse_utils::i32(cmd.tokens[1], "orderId");
        cmd.timestamp = parse_utils::i64(cmd.tokens[2], "timestamp");
        return cmd;
    }

    // M => Match: M,ts  lub  M,ts,symbol
    if (action == 'M') {
        if (cmd.tokens.size() != 2 && cmd.tokens.size() != 3)
            throw std::invalid_argument("wrong field count in token");

        cmd.type = CommandType::Match;
        cmd.timestamp = parse_utils::i64(cmd.tokens[1], "timestamp");
        if (cmd.tokens.size() == 3) cmd.symbol = cmd.tokens[2];
        return cmd;
    }


    if (action == 'D') {
        if (cmd.tokens.size() != 1 && cmd.tokens.size() != 2 && cmd.tokens.size() != 3)
            throw std::invalid_argument("wrong field count in the token");

        cmd.type = CommandType::Dump;

        auto isAllDigits = [](const std::string& s) {
            return !s.empty() && std::all_of(s.begin(), s.end(),
                [](unsigned char c){ return std::isdigit(c); });
        };

        if (cmd.tokens.size() == 1) return cmd;

        if (cmd.tokens.size() == 2) {
            const std::string& a = cmd.tokens[1];
            if (isAllDigits(a)) cmd.timestamp = parse_utils::i64(a, "timestamp");
            else                cmd.symbol = a;
            return cmd;
        }

        // size == 3: Q,<arg1>,<arg2>
        // pozwalamy na oba układy: Q,ts,sym  albo  Q,sym,ts
        const std::string& a = cmd.tokens[1];
        const std::string& b = cmd.tokens[2];

        if (isAllDigits(a)) {
            cmd.timestamp = parse_utils::i64(a, "timestamp");
            cmd.symbol = b;
        } else if (isAllDigits(b)) {
            cmd.symbol = a;
            cmd.timestamp = parse_utils::i64(b, "timestamp");
        } else {
            // oba wyglądają jak symbol -> uznajemy a jako symbol, b jako symbol? lepiej zrejectować:
            throw std::invalid_argument("query expects timestamp and/or symbol");
        }
        return cmd;
    }

    if (action == 'Q') {
        if (cmd.tokens.size() != 1)
            throw std::invalid_argument("wrong field count in the token");
        cmd.type = CommandType::Query;
        return cmd;
    }

    throw std::invalid_argument("unknown action");
}