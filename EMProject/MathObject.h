#pragma once

namespace em {
	namespace math {
		using System::String;
		ref class MathObject abstract{
		public:
			
			static property int numPrecision {
				int get() {
					return precision;
				}

				void set(int p) {
					precision = p;
				}

			}
			static property wchar_t formatSpecifier {
				wchar_t get() {
					return fSpec;
				}

				void set(wchar_t fs) {
					fSpec = fs;
				}

			}

			static property int numWidth {
				int get() {
					return width;
				}

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

		protected:
			static property String^ NUMERAL_FORMAT {
				String^ get() {
					return "{0," + width + ":" + formatSpecifier + precision + "}";
				}
			}

		private:
			String^ const mType;
			String^ const mID;
			static int precision = 6;
			static int width = 11;
			static wchar_t fSpec = 'f';
		public:
			virtual ~MathObject();
			virtual String^ getHeader()abstract;
			virtual String^ ToString()override abstract;
			virtual MathObject^ operator-() abstract;
			virtual MathObject^ overrideAssign(MathObject^ mo) abstract;
		public:
			MathObject(String^ type, String^  mID);
		};
	}
}

