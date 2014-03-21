#pragma once
#include "MathObject.h"

namespace em {
	namespace math {
		using System::Text::StringBuilder;
		using System::Collections::Generic::Dictionary;

		ref class MathObjSet abstract : public MathObject {

		private:
			delegate MathObjSet^ ConcreteSet(String^ typeID);

		private:
			static Dictionary<String^, ConcreteSet^>^ const setConstructors = gcnew Dictionary<String^, ConcreteSet^>();
		public:

			static MathObjSet^ createSpecificSet(MathObject^ element);
		private:
			template<typename M>
			static MathObjSet^ createSetInstance(String^ typeID) {
				return gcnew MathObjGenericSet<M>(typeID);
			}
		public:
			static String^ const TAG = "Set";


			property int size{
				virtual int get() abstract;
			}

		public:
			static MathObjSet();
			virtual ~MathObjSet();
			virtual bool add(MathObject^ mo) abstract;

			static bool setCast(MathObject^ mo, MathObjSet^% set);
		protected:
			MathObjSet(String^ setID);

		};
	}
}
