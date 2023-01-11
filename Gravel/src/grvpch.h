#pragma once

//	precompiled headers for the Gravel Engine
//	speeds up compilation 

#include <iostream> 
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Gravel/Log.h"

#ifdef GRAVEL_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // GRAVEL_PLATFORM_WINDOWS