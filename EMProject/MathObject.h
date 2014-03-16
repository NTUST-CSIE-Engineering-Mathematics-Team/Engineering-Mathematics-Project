#pragma once

namespace em {
	namespace math {
		using System::String;
		ref class MathObject abstract{
		public:
			static property int a;
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

		protected:
			static property String^ NUMERAL_FORMAT {
				String^ get() {
					return "{0," + width + ":F" + precision + "}";
				}
			}

		private:
			String^ mType;

			static int precision = 2;
			static int width = 8;
	
		public:
			virtual ~MathObject();

			virtual String^ ToString()override abstract;
			virtual MathObject^ operator-() abstract;
		public:
			MathObject(String^ type);
		};
	}
}

