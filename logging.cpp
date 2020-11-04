#include "logging.h"

bool Logging::ENABLE_RED_LOG = true;
bool Logging::ENABLE_WHITE_LOG = true;
bool Logging::ENABLE_MAGENTA_LOG = true;
bool Logging::ENABLE_GREEN_LOG = true;
bool Logging::ENABLE_BLUE_LOG = true;
bool Logging::ENABLE_YELLOW_LOG = true;
bool Logging::ENABLE_CYAN_LOG = true;

void Logging::disableLogs()
{
    Logging::ENABLE_RED_LOG = false;
    Logging::ENABLE_WHITE_LOG = false;
    Logging::ENABLE_MAGENTA_LOG = false;
    Logging::ENABLE_GREEN_LOG = false;
    Logging::ENABLE_BLUE_LOG = false;
    Logging::ENABLE_YELLOW_LOG = false;
    Logging::ENABLE_CYAN_LOG = false;

}

void Logging::enableLogs()
{
    Logging::ENABLE_RED_LOG = true;
    Logging::ENABLE_WHITE_LOG = true;
    Logging::ENABLE_MAGENTA_LOG = true;
    Logging::ENABLE_GREEN_LOG = true;
    Logging::ENABLE_BLUE_LOG = true;
    Logging::ENABLE_YELLOW_LOG = true;
    Logging::ENABLE_CYAN_LOG = true;
}
