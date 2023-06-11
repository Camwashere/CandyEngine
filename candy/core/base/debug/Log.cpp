#include "Log.hpp"

namespace Candy
{
    SharedPtr<Logger> Log::coreLogger;
    SharedPtr<Logger> Log::clientLogger;
    
    void Log::Init()
    {
        coreLogger = std::make_shared<Logger>("CANDY");
        clientLogger = std::make_shared<Logger>("APP");
    }
}
