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
        
        dpp::message msg(dotenv::getenv("QUOTES_CID"), "❝" + text + "❞\n\\- " + author);
        g_bot->message_create(msg);
        
        // confirmation message to user that the quote was added
        event.reply("Quote added:\n❝" + text + "❞\n\\- " + author);
    },
    {
        // Parameter list, for use in registering the slash command with Discord
        dpp::command_option(dpp::co_string, "text", "The quote text", true),
        dpp::command_option(dpp::co_string, "author", "Author of the quote", true)
    }
};
