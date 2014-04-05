#pragma once
#include "MathObject.h"

namespace em {
	namespace math {
		using System::Text::StringBuilder;
		using System::Collections::Generic::Dictionary;

		ref class MathObjSet abstract : public MathObject {

		private:
			delegate MathObjSet^ ConcreteSet();

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

			virtual property MathObjSet^ subset[int, int]{
				virtual MathObjSet^ get(int i, int j) abstract;
			}

			virtual property MathObject^ mathObject[int] {
				virtual MathObject^ get(int i) abstract;
			}
		public:
			static MathObjSet();
			virtual ~MathObjSet();

			virtual bool add(MathObject^ mo) abstract;

			static bool setCast(MathObject^ mo, MathObjSet^% set);
			static MathObjSet^ createSpecificSet(String^ typeName);
			
		protected:
			MathObjSet(String^ contentID);
			static String^ getVaildContentID(String^ contentID);

		private:
			generic<typename M> where M : MathObject
			static MathObjSet^ createSetInstance();
		};


	}
}

