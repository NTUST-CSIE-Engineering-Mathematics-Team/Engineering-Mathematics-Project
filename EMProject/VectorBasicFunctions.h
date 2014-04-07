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
						static MathObject^ to_vec$M(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ mag$V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ normlzd$V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ proj$V_V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ compnt$V_V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ angle$V_V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ tri_area$V_V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ is_pallel$V_V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ is_orth$V_V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ plane_norm$V_V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ is_linear_ind$VC(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ gs_orth_process$VC(array<MathObject^>^ mos, Message^% msg);

						static Message^ differentDimErrMsg(String^ funName);
					};
				}
			}
		}
	}
}
