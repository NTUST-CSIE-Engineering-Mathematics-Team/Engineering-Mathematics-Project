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

					interface class MatrixBasicFunctions {

					public:
						static MathObject^ transpose$M(array<MathObject^>^ mos, Message^% msg);
						
					};
				}
			}
		}
	}
}
