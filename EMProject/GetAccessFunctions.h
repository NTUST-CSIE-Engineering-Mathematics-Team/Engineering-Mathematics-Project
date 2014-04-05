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

					interface class GetAccessFunctions {

					public:
						static property Message^ indexIntErrMsg {
							Message^ get() {
								return gcnew Message(Message::State::ERROR, "The index must be an integer");
							}
						}

						static property Message^ indexOBErrMsg {
							Message^ get() {
								return gcnew Message(Message::State::ERROR, "Index out of bounds");
							}
						}

						static MathObject^ get$V_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ get$M_S_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ get$SC_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ get$AC_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ get$VC_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ get$MC_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ get$CC_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ getSetElement(MathObject^ set, MathObject^ i, Message^% msg);

						static MathObject^ subset$SC_S_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ subset$AC_S_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ subset$VC_S_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ subset$MC_S_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ subset$CC_S_S(array<MathObject^>^ mos, Message^% msg);
						static MathObject^ getsubSet(MathObject^ set, MathObject^ i, MathObject^ j, Message^% msg);
					};
				}
			}
		}
	}
}

