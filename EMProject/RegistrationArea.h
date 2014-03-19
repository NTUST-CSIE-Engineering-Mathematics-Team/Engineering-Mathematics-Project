#pragma once

#include "All_Operators.h"
#include "All_Functions.h"
#include "All_Commands.h"

namespace em {
	namespace intrprt {
		using namespace em::intrprt::cmd;
		using namespace em::math::engine::expression::functions;
		using namespace em::math::engine::expression::operators;

		interface class RegistrationArea {
		public:
			static void registerHere();
		};
	}
}