#pragma once

namespace em {
	namespace intrprt {
		using System::String;
		using System::Collections::Specialized::StringCollection;
		using namespace System::Collections;

		ref class KeywordCollection abstract {
		public:
			static String^ const MATRICES = "mats";
			static String^ const VECTORS = "vecs";
			static String^ const SCALARS = "scls";
			static String^ const SETS = "sets";
			static String^ const ANGLES = "agls";
			static String^ const ALL = "all";
			static String^ const SETTINGS_CMD = "option";
			static String^ const PRINT_CMD = "print";
			static String^ const DELETE_CMD = "delete";
			static String^ const STORAGE_CMD = "stg";
			
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
