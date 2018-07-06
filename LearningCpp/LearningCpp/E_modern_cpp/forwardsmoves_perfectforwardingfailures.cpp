#include<iostream>
#include <vector>

namespace
{
	void log(const char* msg) { std::cout << msg << std::endl; }
	class TypeDemo
	{
	public:
	};


	void concrete_func(int param) { std::cout << param << std::endl; }

	template <typename... T>
	void forwarding_func(T&&... forward_ref)		//forward_ref has same meaning as universal reference
	{
		//...do extra work, such as timing function, then forward arguments to real function...
		concrete_func(std::forward<T>(forward_ref)...);
	}

	void pass_container(const std::vector<int>& param) { std::cout << "arg size: " << param.size() << std::endl; }
	template <typename... T> void forwarding_func_container(T&&... forward_ref){
		pass_container(std::forward<T>(forward_ref)...);
	}

	class Button_with_copypaste_constant
	{
	public:
		//this, without a body, will just get copy and pasted in places its used -- rather than giving it a memory address to look up where the variable is located
		static constexpr int constant_val = 20;
	};

	class Button_without_copypaste_constant
	{
	public:
		//this, without a body, will just get copy and pasted in places its used -- rather than giving it a memory address to look up where the variable is located
		static constexpr int constant_val = 30;
	};
	constexpr int Button_without_copypaste_constant::constant_val; //give it a defintion, which gives it a memory address.


	void ovld_func(){}
	void ovld_func(int x) {}
	void driver(void(*fptr)()) { fptr(); }
	template <typename... T> void forwarding_func_to_overload(T&&... forward_ref) {
		driver(std::forward<T>(forward_ref)...);
	}

	template<typename T>	void many_possible_instantiations(T x) { }
	void driver2(void(*fptr)(int)) { fptr(5); }
	template <typename... T> void forward_template_func(T&&... forward_ref)
	{
		driver2(std::forward<T>(forward_ref)...);
	}

	void take_int16(uint16_t x ) { }
	template <typename... T> void forward_for_bitfield(T&&... forward_ref)
	{
		take_int16(std::forward<T>(forward_ref)...);
	}
}

int main()
{
	//perfect forwarding works in most cases, but here are a few situations where it fails.
	//1. When used with braced initialziers
	{
		//this is fine, it creates an initializer list and implicitly converts it to a std::vector to use. 
		pass_container({ 1, 2, 3 });

		//however, there's a standard C++ rule against deducing to std::intializer_list -- compilers are forbidden from deducing things like {1, 2, 3} to initializer lists unless it is declared as an initializer list in the template function
		//forwarding_func_container({ 1, 2, 3 }); //C2660: '`anonymous-namespace'::forwarding_func_container': function does not take 1 arguments

		auto work_around = { 1, 2, 3 }; //creates an initializer list
		forwarding_func_container(work_around);
	}

	//2. 0 and NULL pointers forward incorrectly
	{
		//I think this is pretty straight forward, so I'm not going to write a code example (there was another file on using nullptr).
		//Basically, if you're passing 0 (or NULL) to a function template, the type will deduce to integral type (e.g. int). Which will mess up calls expecting pointers!
		//just use nullptr instead.
	}

	//3. Declaration only data that never gets memory addresses causes issues with perfect forwarding
	{
		//Some declarations do not generaly memory locations, and instead when compilation is being done, the values are just copied and pasted inline.
		//these values are things like constexpr and static const member variables.
		//this copy/paste behavior is call "const propagation"
		std::vector<Button_with_copypaste_constant> container;
		container.reserve(Button_with_copypaste_constant::constant_val); //copy and pastes the value at compile time!

		//const int* ptr = &Button_with_copypaste_constant::constant_val; //by taking address, we prevent copypaste behavior and must give it memory. 
		concrete_func(Button_without_copypaste_constant::constant_val);
		//forwarding_func(Button_without_copypaste_constant::constant_val); //compiles, but should fail linking (some platforms don't respect this and will link)

		concrete_func(Button_with_copypaste_constant::constant_val);
		forwarding_func(Button_with_copypaste_constant::constant_val);

		//note: it seems MSVC doesn't enforce these rules (or I actually need to use multiple src files); but they should be known for portablility
		//gcc also seems to compile and link just fine.
	}

	//4. function pointers that are overloaded cause forwarding issues
	{
		//these are fine because the compiler figures out which overload is needed based on signature of driver (it contains a function pointer)
		driver(&ovld_func);
		driver(ovld_func);

		//forwarding_func_to_overload(&ovld_func); //this cannot know which function to pass!

		using FuncSignature = void(*)();
		FuncSignature func_ptr = ovld_func; //this is the work around
		forwarding_func_to_overload(func_ptr); //we specified the function signature, rather than asking the compiler to figure it out.

		//the same applies to template instantiations as do to overloads.
		driver2(many_possible_instantiations); //will instantiate a template that takes int
		//forward_template_func(many_possible_instantiations);
		using FuncSignatureForTemplate = void(*)(int);
		FuncSignatureForTemplate func_ptr_template = many_possible_instantiations; //this is the work around
		driver2(func_ptr_template);	//we explicitly created a template instantation to pass, so the compiler isn't figuring out the template type 
	}

	//5. bitfields cannot be forwarded because you cannot take an arbitrary address of bits
	{
		struct SomeBitfield
		{
			std::uint16_t
				header : 4,		//gets 4 bits
				body : 8,		//gets 8 bits
				tail : 4		//gets 4 bits
				;
		};

		SomeBitfield packet;
		packet.body = 6;
		packet.header = 1;
		packet.tail = 5;

		take_int16(packet.body); //makes a copy of the argument (if we pass const& it will make a copy then pass the copy as a const ref.

		//we can't take references of bitfields because individual bits are not addressable! (and references use pointers underneath)
		//forward_for_bitfield_willfail(packet.body); cannot get a reference to field, thus we can't forward it!

		//work around is to make a copy upfront (because bitfields fields must be passed as copies anyways)
		uint16_t body = packet.body;
		forward_for_bitfield(body);
	}

	std::cin.get();
}