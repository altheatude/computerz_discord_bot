#include "dotenv.h"
#include <dpp/dpp.h>
#include <iostream>
#include "aq.h"

// const std::string BOT_TOKEN = std::getenv("BOT_TOKEN");
// dpp::cluster bot(BOT_TOKEN);

dpp::cluster* g_bot = nullptr;

int main()
{
    dotenv::init("../.env");
    const std::string BOT_TOKEN = dotenv::getenv("BOT_TOKEN");

    dpp::cluster bot(BOT_TOKEN);
    g_bot = &bot; // Store global reference

    bot.on_log(dpp::utility::cout_logger());

    // Creates a Handler type for readability
    using Handler = std::function<void(const dpp::slashcommand_t &)>;

    // A map makes matching commands to their handlers faster
    std::unordered_map<std::string, Handler> command_handlers;
    // A list of slash commands to register with Discord
    std::vector<dpp::slashcommand> slash_commands;
    // A list of all commands to register (struct Command)
    std::vector<Command> all_commands = {ping_command, quote_command};

    for (const auto &cmd : all_commands) {
        // Match the command name to its handler in c_h map
        command_handlers[cmd.name] = cmd.handler;

        // Create a slash command with the command's name and description
        dpp::slashcommand sc(cmd.name, cmd.description, bot.me.id);

        // Loop through the command's options and add them to the slash command (sc)
        for (const auto &opt : cmd.options) {
            sc.add_option(opt);
        }
        
        // Create a slash command to register with Discord in the s_c vector
        slash_commands.push_back(sc);
    }

    // Runs the appropriate handler when a slash command is received
    bot.on_slashcommand([&command_handlers](const dpp::slashcommand_t &event) {
        auto it = command_handlers.find(event.command.get_command_name());
        if (it != command_handlers.end()) {
            it->second(event);
        } });

    // Register the slash commands with Discord when the bot is ready
    bot.on_ready([&bot, &slash_commands](const dpp::ready_t &event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.guild_bulk_command_create(slash_commands, 1555961563570114692);
        } });

    bot.start(dpp::st_wait);

    return 0;
}