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
			static String^ const TAG = "Set";
			static String^ const ID = "C";

			property int size{
				virtual int get() abstract;
			}

			property String^ contentID {
				String^ get() {
					return this->mathID[0].ToString();
				}
			}

		public:
			static MathObjSet();
			virtual ~MathObjSet();
			virtual bool add(MathObject^ mo) abstract;

			static bool setCast(MathObject^ mo, MathObjSet^% set);
			static MathObjSet^ createSpecificSet(MathObject^ element);

		protected:
			MathObjSet(String^ contentID);

		private:
			template<typename M>
			static MathObjSet^ createSetInstance(String^ typeID) {
				return gcnew MathObjGenericSet<M>(typeID);
			}

		};


	}
}
