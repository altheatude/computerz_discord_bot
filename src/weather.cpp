#include "aq.h"

#include <iomanip>

// Purpose: Weather feature for the discord bot using the open meteo API
// Documentation: https://open-meteo.com/en/docs

// Translates weather code into readable format
std::string getWeatherDescription(int weather_code)
{
    switch (weather_code)
    {
        case 0:  return "Clear sky";
        case 1:  return "Mainly clear";
        case 2:  return "Partly cloudy";
        case 3:  return "Overcast";
        case 45: return "Fog";
        case 48: return "Depositing rime fog";
        case 51: return "Light drizzle";
        case 53: return "Moderate drizzle";
        case 55: return "Dense drizzle";
        case 56: return "Light freezing drizzle";
        case 57: return "Dense freezing drizzle";
        case 61: return "Slight rain";
        case 63: return "Moderate rain";
        case 65: return "Heavy rain";
        case 66: return "Light freezing rain";
        case 67: return "Heavy freezing rain";
        case 71: return "Slight snowfall";
        case 73: return "Moderate snowfall";
        case 75: return "Heavy snowfall";
        case 77: return "Snow grains";
        case 80: return "Slight rain showers";
        case 81: return "Moderate rain showers";
        case 82: return "Violent rain showers";
        case 85: return "Slight snow showers";
        case 86: return "Heavy snow showers";
        case 95: return "Thunderstorm";
        case 96: return "Thunderstorm with slight hail";
        case 97: return "Heavy thunderstorm";
        case 99: return "Thunderstorm with heavy hail";
        default: return "Unknown weather condition";        
    }
}

// Actual weather command itself
const Command weather_command = 
{
    "weather",
    "Gets the weather in Kingston ON and puts it in chat",
    [](const dpp::slashcommand_t& event) 
    {
        const std::string url =
            "https://api.open-meteo.com/v1/forecast?" 
            "latitude=44.2312&longitude=-76.4860" 
            "&current=temperature_2m,relative_humidity_2m," 
            "apparent_temperature,weather_code,wind_speed_10m";

        // Make the web request    
        g_bot->request 
        (
            url,
            dpp::m_get,
            [event](const dpp::http_request_completion_t& response) 
            {
                if (response.status != 200) 
                {
                    event.reply("Failed to get weather data.");
                    return;
                }

                // Extracts all values from the JSON and gives them a variable
                dpp::json weather_data = dpp::json::parse(response.body);
                double temperature     = weather_data["current"]["temperature_2m"];
                int    humidity        = weather_data["current"]["relative_humidity_2m"];
                double feels_like      = weather_data["current"]["apparent_temperature"];
                double wind_speed      = weather_data["current"]["wind_speed_10m"];
                int    weather_code    = weather_data["current"]["weather_code"];

                // Convert the doubles to 1 decimal place
                std::ostringstream temperature_text;
                temperature_text << std::fixed << std::setprecision(1) << temperature;
                std::ostringstream feels_like_text;
                feels_like_text  << std::fixed << std::setprecision(1) << feels_like;
                std::ostringstream wind_text;
                wind_text        << std::fixed << std::setprecision(1) << wind_speed;

                // Gets the weather description
                std::string description = getWeatherDescription(weather_code);

                // What the bot outputs to discord
                event.reply
                (
                    "Temperature: " + temperature_text.str() + " C\n" + 
                    "Humidity: "    + std::to_string(humidity) + "%\n" +
                    "Feels like: "  + feels_like_text.str() + " C\n" + 
                    "Wind: "        + wind_text.str() + " km/h\n" + 
                    "Conditions: "  + description
                );
            }
        ); 
    }
};