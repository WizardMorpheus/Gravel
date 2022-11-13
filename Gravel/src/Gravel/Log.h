#pragma once
#include "grvpch.h"

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>
//#include <spdlog/fmt/fmt.h>


namespace Gravel {

	class GRAVEL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Client logging macros
#define GRAVEL_CLIENT_TRACE(...)		Gravel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GRAVEL_CLIENT_DEBUG(...)		Gravel::Log::GetClientLogger()->debug(__VA_ARGS__)
#define GRAVEL_CLIENT_CRITICAL(...)		Gravel::Log::GetClientLogger()->critical(__VA_ARGS__)
#define GRAVEL_CLIENT_INFO(...)			Gravel::Log::GetClientLogger()->info(__VA_ARGS__)
#define GRAVEL_CLIENT_WARN(...)			Gravel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GRAVEL_CLIENT_ERROR(...)		Gravel::Log::GetClientLogger()->error(__VA_ARGS__)

//core logging macros
#define GRAVEL_CORE_TRACE(...)			Gravel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GRAVEL_CORE_DEBUG(...)			Gravel::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define GRAVEL_CORE_CRITICAL(...)		Gravel::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define GRAVEL_CORE_INFO(...)			Gravel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GRAVEL_CORE_WARN(...)			Gravel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GRAVEL_CORE_ERROR(...)			Gravel::Log::GetCoreLogger()->error(__VA_ARGS__)
