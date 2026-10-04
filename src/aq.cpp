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
        // Extract parameter
        std::string text = std::get<std::string>(event.get_parameter("text"));
        std::string author = std::get<std::string>(event.get_parameter("author"));
        event.reply("Quote added:\n\"" + text + "\"\n\\- " + author);
    },
    {
        // Parameter list
        dpp::command_option(dpp::co_string, "text", "The quote text", true),
        dpp::command_option(dpp::co_string, "author", "Author of the quote", true)
    }
};
