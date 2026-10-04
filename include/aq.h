#pragma once
#include <dpp/dpp.h>
#include "dotenv.h"

extern dpp::cluster* g_bot;

struct Command {
    std::string name;
    std::string description;
    std::function<void(const dpp::slashcommand_t&)> handler;
    std::vector<dpp::command_option> options = {};
};

extern const Command ping_command;
extern const Command quote_command;