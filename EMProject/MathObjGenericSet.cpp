#include "MathObjGenericSet.h"
#include "PrintCommand.h"

using namespace em::math;
using em::intrprt::cmd::PrintCommand;

generic<typename M> where M : MathObject
MathObjGenericSet<M>::MathObjGenericSet(String^ objID) : MathObjSet(objID + "C") {
	this->list = gcnew LinkedList<M>();
	
}

generic<typename M> where M : MathObject
MathObjGenericSet<M>::MathObjGenericSet(MathObjGenericSet<M>^ ms) : MathObjSet(ms->mathID) {
	this->list = gcnew LinkedList<M>(ms->list);
}

generic<typename M> where M : MathObject
MathObjGenericSet<M>::~MathObjGenericSet() {
	delete this->list;
}

generic<typename M> where M : MathObject
MathObject^ MathObjGenericSet<M>::operator-() {
	MathObjGenericSet<M>^ newSet = emptyClone();
	for each(M mo in this) {
		newSet->add(safe_cast<M>(-mo));
	}
	
	return newSet;
}

generic<typename M> where M : MathObject
bool MathObjGenericSet<M>::add(MathObject^ mo) {
	if (!String::Concat(mo->mathID, "C")->Equals(this->mathID)) {
		return false;
	}

	this->add(safe_cast<M>(mo));
	return true;
}

generic<typename M> where M : MathObject
void MathObjGenericSet<M>::add(M mo) {
	this->list->AddLast(mo);
}

generic<typename M> where M : MathObject
String^ MathObjGenericSet<M>::ToString() {
	StringBuilder^ sb = gcnew StringBuilder("{");
	
	for each(M mo in this) {
		sb->AppendFormat("\n   {0}\n   {1}\n", PrintCommand::buildHeader(mo), mo->ToString()->Replace("\n", "\n   "));
	}
	
	sb->Append("}");

	return sb->ToString();
}

generic<typename M> where M : MathObject
IEnumerator<M>^ MathObjGenericSet<M>::GetEnumerator() {
	return this->list->GetEnumerator();
}

generic<typename M> where M : MathObject
System::Collections::IEnumerator^ MathObjGenericSet<M>::GetNGEnumerator() {
	return this->GetEnumerator();
}

generic<typename M> where M : MathObject
bool MathObjGenericSet<M>::gSetCast(MathObject^ mo, MathObjGenericSet<M>^% set) {
	set = dynamic_cast<MathObjGenericSet<M>^>(mo);
	return set != nullptr;
}

generic<typename M> where M : MathObject
MathObjGenericSet<M>^ MathObjGenericSet<M>::emptyClone() {
	return gcnew MathObjGenericSet<M>(this->mathID->Substring(0, this->mathID->Length - 1));
}

