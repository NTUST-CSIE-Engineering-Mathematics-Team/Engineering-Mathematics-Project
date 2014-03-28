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

					interface class TrigonometricFunctions {

					public:
						static MathObject^ angle$S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ sin$A(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ cos$A(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ tan$A(array<MathObject^>^ mos, Message^% msg);
					};
				}
			}
		}
	}
}
