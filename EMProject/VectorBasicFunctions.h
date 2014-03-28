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

					interface class VectorBasicFunctions {

					public:
						static MathObject^ mag$V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ normlzd$V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ proj$V_V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ compnt$V_V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ angle$V_V(array<MathObject^>^ mos, Message^% msg);

						static Message^ differentRankErrMsg();
					};
				}
			}
		}
	}
}
