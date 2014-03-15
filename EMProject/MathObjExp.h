#pragma once
#include "Expression.h"
#include "VariableTable.h"

namespace em {
	namespace math {
		namespace engine {
			using em::intrprt::VariableTable;
			ref class MathObjExp : public Expression {
			private:
				MathObject^ mo;

			public:
				MathObjExp(MathObject^ mo);
				virtual ~MathObjExp();

				virtual MathObject^ compute() override;
			};

		}
	}
}