#pragma once
#include "All_Math.h"
#include "Message.h"

namespace em {
	namespace math {
		namespace engine {
			namespace expression {
				namespace functions {
					using namespace em::math;
					using em::intrprt::Message;
					using em::math::MathHelper;
					using System::Math;

					interface class ScalarBasicFunctions {

					public:
						static MathObject^ pow$S_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ test(array<MathObject^>^ mos, Message^% msg);
					};
				}
			}
		}
	}
}
