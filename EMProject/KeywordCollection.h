#pragma once

namespace em {
	namespace intrprt {
		using System::String;
		using System::Collections::Specialized::StringCollection;
		using namespace System::Collections;

		ref class KeywordCollection abstract {
		public:
			static String^ const MATRIX = "mat";
			static String^ const VECTOR = "vec";
			static String^ const SCALAR = "scl";
			static String^ const ALL = "all";
			static String^ const SETTINGS_CMD = "option";
			static String^ const PRINT_CMD = "print";
			static String^ const DELETE_CMD = "delete";
			static String^ const STORAGE_CMD = "stg";
			static String^ const JUDGE_CMD = "judge";
			
		private:
			static StringCollection^ const keywordsSet = gcnew StringCollection();

		public:
			virtual ~KeywordCollection();

			static bool contains(String^ keywords);
		private:
			KeywordCollection();
			static KeywordCollection();

		};
	}
}
