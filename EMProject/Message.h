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
			State type;
			String^ const content;

		public:
			property State msgType{
				virtual State get() sealed {
					return type;
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
