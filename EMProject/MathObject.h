#pragma once

namespace em {
	namespace math {
		using System::String;
		ref class MathObject abstract{
		public:
			
			static property int numPrecision {
				void set(int p) {
					precision = p;
				}
			}

			static property int numWidth {
				void set(int w) {
					if (w > precision) {
						width = w;
					}
				}
			}

			property String^ mathType{
				String^ get() {
					return mType;
				}
			}

			property String^ mathID{
				String^ get() {
					return mID;
				}
			}

			property MathObject^ clone{
				virtual MathObject^ get() abstract;
			}

		protected:
			static property String^ NUMERAL_FORMAT {
				String^ get() {
					return "{0," + width + ":F" + precision + "}";
				}
			}

		private:
			String^ const mType;
			String^ const mID;
			static int precision = 2;
			static int width = 7;
	
		public:
			virtual ~MathObject();

			virtual String^ ToString()override abstract;
			virtual MathObject^ operator-() abstract;
			virtual MathObject^ overrideAssign(MathObject^ mo) abstract;
		public:
			MathObject(String^ type, String^  mID);
		};
	}
}

