#include "aq.h"

const Command ping_command = {
    "ping",
    "Ping pong!",
    [](const dpp::slashcommand_t& event) {
        event.reply("Pong!");
    }
};

const Command quote_command = {
    "quote",
    "Enter quote to be sent to the quotes channel",
    [](const dpp::slashcommand_t& event) {
        event.reply("quote");
    }
};
