#pragma once
#include "Log.hpp"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

namespace Candy::Debug
{
    using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;
    
    struct ProfileResult
    {
        std::string name;
        
        FloatingPointMicroseconds start;
        std::chrono::microseconds elapsedTime;
        std::thread::id threadID;
    };
    
    struct ProfileSession
    {
        std::string name;
    };
    
    class Profiler
    {
    private:
        std::mutex mutex;
        ProfileSession* currentSession;
        std::ofstream outputStream;
    
    private:
        Profiler()
                : currentSession(nullptr)
        {
        }
        
        ~Profiler()
        {
            EndSession();
        }
        
        void WriteHeader()
        {
            outputStream << R"({"otherData": {},"traceEvents":[{})";
            outputStream.flush();
        }
        
        void WriteFooter()
        {
            outputStream << "]}";
            outputStream.flush();
        }
        
        // Note: you must already own lock on mutex before
        // calling InternalEndSession()
        void InternalEndSession()
        {
            if (currentSession)
            {
                WriteFooter();
                outputStream.close();
                delete currentSession;
                currentSession = nullptr;
            }
        }
    public:
        Profiler(const Profiler&) = delete;
        Profiler(Profiler&&) = delete;
        
        inline void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            std::lock_guard lock(mutex);
            if (currentSession)
            {
                // If there is already a current session, then close it before beginning new one.
                // Subsequent profiling output meant for the original session will end up in the
                // newly opened session instead.  That's better than having badly formatted
                // profiling output.
                if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
                {
                    CANDY_CORE_ERROR("Profiler::BeginSession('{0}') when session '{1}' already open.", name, currentSession->name);
                }
                InternalEndSession();
            }
            outputStream.open(filepath);
            
            if (outputStream.is_open())
            {
                currentSession = new ProfileSession({name});
                WriteHeader();
            }
            else
            {
                if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
                {
                    CANDY_CORE_ERROR("Profiler could not open results file '{0}'.", filepath);
                }
            }
        }
        
        void EndSession()
        {
            std::lock_guard lock(mutex);
            InternalEndSession();
        }
        
        void WriteProfile(const ProfileResult& result)
        {
            std::stringstream json;
            
            json << std::setprecision(3) << std::fixed;
            json << ",{";
            json << "\"cat\":\"function\",";
            json << "\"dur\":" << (result.elapsedTime.count()) << ',';
            json << "\"name\":\"" << result.name << "\",";
            json << "\"ph\":\"X\",";
            json << "\"pid\":0,";
            json << "\"tid\":" << result.threadID << ",";
            json << "\"ts\":" << result.start.count();
            json << "}";
            
            std::lock_guard lock(mutex);
            if (currentSession)
            {
                outputStream << json.str();
                outputStream.flush();
            }
        }
        
        static Profiler& Get()
        {
            static Profiler instance;
            return instance;
        }
   
    
    };
    
    class ProfilerTimer
    {
    private:
        const char* name;
        std::chrono::time_point<std::chrono::steady_clock> startTimepoint;
        bool stopped;
    
    public:
        ProfilerTimer(const char* nameValue)
                : name(nameValue), stopped(false)
        {
            startTimepoint = std::chrono::steady_clock::now();
        }
        
        ~ProfilerTimer()
        {
            if (!stopped)
                Stop();
        }
        
        void Stop()
        {
            auto endTimepoint = std::chrono::steady_clock::now();
            auto highResStart = FloatingPointMicroseconds{ startTimepoint.time_since_epoch() };
            auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint).time_since_epoch();
            
            Profiler::Get().WriteProfile({ name, highResStart, elapsedTime, std::this_thread::get_id() });
            
            stopped = true;
        }
        
    };
    
    namespace ProfilerUtils {
        
        template <size_t N>
        struct ChangeResult
        {
            char Data[N];
        };
        
        template <size_t N, size_t K>
        constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
        {
            ChangeResult<N> result = {};
            
            size_t srcIndex = 0;
            size_t dstIndex = 0;
            while (srcIndex < N)
            {
                size_t matchIndex = 0;
                while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
                    matchIndex++;
                if (matchIndex == K - 1)
                    srcIndex += matchIndex;
                result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
                srcIndex++;
            }
            return result;
        }
    }
    
}

#define CANDY_PROFILE 1
#if CANDY_PROFILE
// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define CANDY_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define CANDY_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define CANDY_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define CANDY_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define CANDY_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define CANDY_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define CANDY_FUNC_SIG __func__
	#else
		#define CANDY_FUNC_SIG "CANDY_FUNC_SIG unknown!"
	#endif

	#define CANDY_PROFILE_BEGIN_SESSION(name, filepath) ::Candy::Debug::Profiler::Get().BeginSession(name, filepath)
	#define CANDY_PROFILE_END_SESSION() ::Candy::Debug::Profiler::Get().EndSession()
	#define CANDY_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::Candy::Debug::ProfilerUtils::CleanupOutputString(name, "__cdecl ");\
											   ::Candy::Debug::ProfilerTimer timer##line(fixedName##line.Data)
	#define CANDY_PROFILE_SCOPE_LINE(name, line) CANDY_PROFILE_SCOPE_LINE2(name, line)
	#define CANDY_PROFILE_SCOPE(name) CANDY_PROFILE_SCOPE_LINE(name, __LINE__)
	#define CANDY_PROFILE_FUNCTION() CANDY_PROFILE_SCOPE(CANDY_FUNC_SIG)
#else
#define CANDY_PROFILE_BEGIN_SESSION(name, filepath)
#define CANDY_PROFILE_END_SESSION()
#define CANDY_PROFILE_SCOPE(name)
#define CANDY_PROFILE_FUNCTION()
#endif