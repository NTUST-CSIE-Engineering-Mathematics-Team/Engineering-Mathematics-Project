#pragma once

namespace em {
	namespace math {
		using System::String;
		ref class MathObject abstract{
		private:
			String^ mType;
		public:
			property String^ mathType{
				String^ get() {
					return mType;
				}
			}

			MathObject(String^ type);
			virtual ~MathObject();

			virtual String^ toString() abstract;
		
		};
	}
}

