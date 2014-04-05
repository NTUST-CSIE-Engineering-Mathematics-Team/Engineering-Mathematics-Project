#pragma once
#include "MathObjSet.h"

namespace em {
	namespace math {
		
		using System::Text::StringBuilder;
		using System::Collections::Generic::List;

		generic<typename M> where M : MathObject
		ref class MathObjGenericSet : public MathObjSet, public System::Collections::Generic::IEnumerable<M> {

		private:
			List<M>^ list;

		public:
			property MathObjGenericSet<M>^ clone{
				MathObjGenericSet<M>^ get() {
					return gcnew MathObjGenericSet<M>(this);
				}
			}

			property int size{
				virtual int get() override {
					return list->Count;
				}
			}

			property M default[int] {
				virtual M get(int i) {
					return this->list[i];
				}
				virtual void set(int i, M mo) {
					this->list[i] = mo;
				}
			}

			virtual property MathObject^ mathObject[int] {
				virtual MathObject^ get(int i) override;
			}

			virtual property MathObjSet^ subset[int, int]{
				virtual MathObjSet^ get(int i, int j) override;
			}
		public:

			MathObjGenericSet();
			MathObjGenericSet(int size);
			MathObjGenericSet(MathObjGenericSet<M>^ set);
			virtual ~MathObjGenericSet();
			
			virtual bool add(MathObject^ mo) override;

			virtual String^ getHeader() override;
			virtual String^ ToString() override;

			virtual MathObject^ operator-() override;
			virtual MathObject^ overrideAssign(MathObject^ mo) override;


			MathObjGenericSet<M>^ overrideAssign(MathObjGenericSet<M>^ mo);
			virtual System::Collections::Generic::IEnumerator<M>^ GetEnumerator();
			virtual void add(M mo);
			
			static bool gSetCast(MathObject^ mo, MathObjGenericSet<M>^% set);
			
		private:

			virtual System::Collections::IEnumerator^ GetNGEnumerator() sealed = System::Collections::IEnumerable::GetEnumerator;
			MathObjGenericSet<M>^ emptyClone();
		};

	}
}