#include "grvpch.h"

#include "Log.h"

namespace Gravel 
{

	//	ccreation of core and client loggers.
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	
	//	Initialisation function, sets the logging format and levels of loggers to trace.
	void Log::Init()
	{
		// Logging message format
		//("[%d/%m/%Y][%T.%e] %n[%^%l%$]: %v --- in %!() at %@")
		//expands to:
		//  [DD/MM/YYYY][Hrs:min:sec.mili] Logger[level(colour)]: message --- in funciton() at fileDir:Line
		spdlog::set_pattern("[%d/%m/%Y][%T.%e] %n[%^%l%$]: %v");

		//creates the Core logger and sets the level
		s_CoreLogger = spdlog::stdout_color_mt("GRAVEL");
		s_CoreLogger->set_level(spdlog::level::trace);

		//creates the Client Logger and sets the level
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}