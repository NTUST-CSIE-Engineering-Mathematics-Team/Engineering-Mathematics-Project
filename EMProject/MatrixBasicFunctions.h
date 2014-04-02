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
						static MathObject^ row_ech$M(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ solve_linear$M_V(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ solve_linear$M_M(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ inverse$M(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ det$M(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ rank$M(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ ul_decom$M(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ pow$M_S(array<MathObject^>^ mos, Message^% msg);

						static void dealLinearSystemResult(Matrix::SolutionState ss, Message^% msg);
						static Message^ notSquareErrMsg(String^ funName);
					};
				}
			}
		}
	}
}
