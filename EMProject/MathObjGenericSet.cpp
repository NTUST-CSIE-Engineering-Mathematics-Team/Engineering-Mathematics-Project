#include "MathObjGenericSet.h"
#include "PrintCommand.h"
#include "MathHelper.h"

using namespace em::math;
using em::intrprt::cmd::PrintCommand;

generic<typename M> where M : MathObject
MathObjGenericSet<M>::MathObjGenericSet() : MathObjSet(MathHelper::getGenericMathID<M>()) {
	this->list = gcnew List<M>();
}

generic<typename M> where M : MathObject
MathObjGenericSet<M>::MathObjGenericSet(int size) : MathObjSet(MathHelper::getGenericMathID<M>()) {
	this->list = gcnew List<M>(size);
}

generic<typename M> where M : MathObject
MathObjGenericSet<M>::MathObjGenericSet(MathObjGenericSet<M>^ ms) : MathObjSet(ms->contentID) {
	this->overrideAssign(ms);
}

generic<typename M> where M : MathObject
MathObjGenericSet<M>::~MathObjGenericSet() {
	delete this->list;
}

generic<typename M> where M : MathObject
MathObjSet^ MathObjGenericSet<M>::subset::get(int i, int j) {
	if (i > j || i >= size || j >= size) {
		return nullptr;
	}

	MathObjGenericSet<M>^ subset = gcnew MathObjGenericSet<M>(j - i + 1);
	for (int k = i; k <= j; k++) {
		subset->add(this[k]);
	}
	return subset;
}

generic<typename M> where M : MathObject
MathObject^ MathObjGenericSet<M>::mathObject::get(int i) {
	if (i < 0 || i >= this->size) {
		return nullptr;
	}
	return this[i];
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
	if (!getVaildContentID(mo->mathID)->Equals(this->contentID)) {
		return false;
	}

	this->add(safe_cast<M>(mo));
	return true;
}

generic<typename M> where M : MathObject
void MathObjGenericSet<M>::add(M mo) {
	this->list->Add(mo);
}

generic<typename M> where M : MathObject
MathObjGenericSet<M>^ MathObjGenericSet<M>::overrideAssign(MathObjGenericSet<M>^ mo) {
	delete this->list;
	this->list = gcnew List<M>(mo->list);

	return this;
}

generic<typename M> where M : MathObject
MathObject^ MathObjGenericSet<M>::overrideAssign(MathObject^ mo) {
	MathObjGenericSet<M>^ tmp;
	if (!gSetCast(mo, tmp)) {
		return nullptr;
	}

	return this->overrideAssign(tmp);
}

generic<typename M> where M : MathObject
String^ MathObjGenericSet<M>::getHeader() {

	StringBuilder^ sb = gcnew StringBuilder(TAG);
	sb->AppendFormat(" of {0}s size = {1}", MathHelper::getGenericMathType<M>()->ToLower(), this->size);

	return sb->ToString();
}

generic<typename M> where M : MathObject
String^ MathObjGenericSet<M>::ToString() {
	
	StringBuilder^ sb = gcnew StringBuilder(getHeader());
	sb->Append("\n{\n");
	for each(M mo in this) {
		sb->AppendFormat("   {0}\n\n", mo->ToString()->Replace("\n", "\n   "));
	}

	sb->Remove(sb->Length - 1, 1);
	sb->Append("}");

	return sb->ToString();
}

generic<typename M> where M : MathObject
System::Collections::Generic::IEnumerator<M>^ MathObjGenericSet<M>::GetEnumerator() {
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
	return gcnew MathObjGenericSet<M>();
}

