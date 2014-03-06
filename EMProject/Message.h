#pragma once
namespace em {
	namespace intrprt {
		using System::String;

		ref class Message {

		public:
			enum class State {
				ERROR, PASS, PARSING
			};

		private:
			State state;
			String^ const content;

		public:
			property State msgState{
				virtual State get() sealed {
					return state;
				}
			}
			property String^ msgContent {
				virtual String^ get() sealed {
					return this->content;
				}
			}

			Message(State t, String^ s);
			virtual ~Message();
		};
	}
}
