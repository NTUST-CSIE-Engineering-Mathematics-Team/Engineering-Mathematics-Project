#pragma once
namespace em {
	using System::String;

	ref class Message {
		
	public:
		enum class Type{
			Error, Pass
		};

	private:
		Type type;
		String^ const content;

	public:
		property Type msgType{
			virtual Type get() sealed {
				return type;
			}
		}
		property String^ msgContent {
			virtual String^ get() sealed {
				return this->content;
			}
		}

		Message(Type t, String^ s);
		virtual ~Message();
	};
}
