#pragma once

namespace em {
	namespace intrprt {
		using System::String;

		interface class KeywordCollection {
		public:
			static String^ const CREATE_MATRIX_COMMAND = "mat";
			static String^ const CREATE_VECTOR_COMMAND = "vec";
			static String^ const CREATE_SCALAR_COMMAND = "scl";
			static String^ const SETTINGS_COMMAND = "set";
			static String^ const PRINT_COMMAND = "print";
			static String^ const DELETE_COMMAND = "delete";

			static KeywordCollection();

		};
	}
}
