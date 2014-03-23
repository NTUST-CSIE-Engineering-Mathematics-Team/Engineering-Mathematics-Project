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

					ref class TrigonometricFunctions {

					public:
						static MathObject^ sin$S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ cos$S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ tan$S(array<MathObject^>^ mos, Message^% msg);
					};
				}
			}
		}
	}
}
