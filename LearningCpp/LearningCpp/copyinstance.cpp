//Writing function for copying polymoprhically, this doesn't however make a blank-state object 

template <class C>
C& new_poly(C& copyObj) {
	//could make this variadic to potentially add arguments
	C* genericPtr = new C;
}
