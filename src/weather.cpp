#include "aq.h"

// Purpose: Weather feature for the discord bot

const Command weather_command = {
    "weather",
    "Gets the weather in Kingston ON and puts it in chat",
    [](const dpp::slashcommand_t& event) {
    
        const std::string url =
            "https://api.open-meteo.com/v1/forecast?" 
            "latitude=44.2312&longitude=-76.4860" 
            "&current=temperature_2m,relative_humidity_2m," 
            "apparent_temperature,weather_code,wind_speed_10m";

        // Make the web request    
        g_bot->request (
            url,
            dpp::m_get,
            [event](const dpp::http_request_completion_t& response) 
            {
                if (response.status != 200) 
                {
                    event.reply("Failed to get weather data.");
                    return;
                }

                event.reply(response.body);
            }
        ); 
    }
};