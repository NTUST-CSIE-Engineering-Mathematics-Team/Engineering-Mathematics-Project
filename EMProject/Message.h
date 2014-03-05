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
			Type get() {
				return type;
			}
		}
		property String^ msgContent{
			String^ get() {
				return this->content;
			}
		}

		Message(Type t, String^ s);
		virtual ~Message();
	};
}
