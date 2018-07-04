#include<iostream>
#include<cstring>
#include <unordered_map>

namespace
{
	void log(const char* msg){std::cout << msg << std::endl;}

	constexpr unsigned BufferSize = 10;
	using BufferType = int[BufferSize];

	//cpp11 strongly encouraged the rule of 3, but it isn't enforced. The default of any of the big three will be generated if not provided
	//its now strongly desired that declaring of the 3 would prevent automatic genreation of the other 2, but that would break legacy code
	//in cpp11 it is now deprecated to relie on special member function generation if you define any of the 3 functions.
	class RuleOfThree
	{
		int *buffer;
	public:
		RuleOfThree() { buffer = new BufferType; }

		//The Big Three!
		~RuleOfThree()                                       { delete buffer;                                   log("dtor"); }
		RuleOfThree(const RuleOfThree& copy) : RuleOfThree() { memcpy(buffer, copy.buffer, sizeof(BufferType)); log("copy ctor"); } //Note: the initializer list calls the noarg ctor (this is cpp11 feature)
		RuleOfThree& operator=(const RuleOfThree& copy)      { memcpy(buffer, copy.buffer, sizeof(BufferType)); log("oper="); return *this; }

		void fillBuffer() { for (unsigned i = 0; i < BufferSize; ++i) { buffer[i] = i; } }
		void printBuffer() { for (unsigned i = 0; i < BufferSize; ++i) { std::cout << buffer[i] << " "; } std::cout << std::endl; }
	};
	//---------------------------------------------------------------

	//cpp14 adds two more special member functions, the move ctor and operator=. 
	//these have slightly different rules than the previous special member functions.
	//1. declaring one of the move assignment operators prevents automatic generation of ALL of the other special member functions! (because if you're using a cpp11 feature, then they would like to enforce rule of 3 too) 
	//2. declaring one of the original three(copy_ctor, copy_=, or dtor), prevents automatic generation of any of the move operators
	class FiveRule
	{
		int *buffer;
	public:
		FiveRule() { buffer = new BufferType; }

		//The Big Five!
		~FiveRule()                                 { delete buffer;                                   /*log("dtor");*/ }
		FiveRule(const FiveRule& copy) : FiveRule() { memcpy(buffer, copy.buffer, sizeof(BufferType)); log("copy ctor"); } //Note: the initializer list calls the noarg ctor (this is cpp11 feature)
		FiveRule& operator=(const FiveRule& copy)   { memcpy(buffer, copy.buffer, sizeof(BufferType)); log("oper="); return *this; }
		FiveRule(FiveRule&& move)                   { buffer = move.buffer; move.buffer = nullptr;     log("move ctor"); } //Note: the initializer list calls the noarg ctor (this is cpp11 feature)
		FiveRule& operator=(FiveRule&& move)        { buffer = move.buffer; move.buffer = nullptr;     log("move oper="); return *this; }

		void fillBuffer() { for (unsigned i = 0; i < BufferSize; ++i) { buffer[i] = i; } }
		void printBuffer() { for (unsigned i = 0; i < BufferSize; ++i) { std::cout << buffer[i] << " "; } std::cout << std::endl; }
		int* getBuffer() { return buffer; }
	};

}

class EsotericCaveat;

//template<typename T>
//using rvalue_cast = std::move<T>;

void special_case();

static int main_v()
{


	log("Rule of Three Demo");
	RuleOfThree obj1;
	obj1.fillBuffer();

	RuleOfThree copy1(obj1);
	copy1.printBuffer();

	RuleOfThree copy2 = copy1; //copy ctor
	copy2 = obj1; //assignment operator

	//------------------------------------------
	log("\n\n\n\nRule of Five Demo");

	FiveRule f1;

	FiveRule fcopy1(f1); //copy ctor
	FiveRule fcopy2 = fcopy1; //copy ctor
	fcopy2 = f1; //copy operator=

	//remember, std::move is essentially a forced cast to an rvalue
	//below use anonymous objects rvalue to mvoe from(compiler optimizations may treat these ase non-rvalues so I'm using move to force)
	FiveRule f2(std::move(FiveRule{})); //move ctor
	FiveRule f3 = std::move(FiveRule{}); //move ctor
	f3 = std::move(FiveRule{}); //move=  

	//------------------------------------------
	log("\n\n\n\nDefinig virtual dtors can remove otherwise good special member functions... add them back with default!");

	class BaseClassesNeedVirtualDtors
	{
	public:
		//the line below removes generation of move operations, even though they're appropriate
		//we just need to induce virtual so that polymorphism behaves correctly with deletes
		virtual ~BaseClassesNeedVirtualDtors() = default;

		//the 5, moves were deleted by defining a dtor, but we can add them back this way.
		BaseClassesNeedVirtualDtors() = default;
		BaseClassesNeedVirtualDtors(const BaseClassesNeedVirtualDtors& copy) = default;
		BaseClassesNeedVirtualDtors& operator=(const BaseClassesNeedVirtualDtors& copy) = default;
		BaseClassesNeedVirtualDtors(BaseClassesNeedVirtualDtors&& move) = default;
		BaseClassesNeedVirtualDtors& operator=(BaseClassesNeedVirtualDtors&& move) = default;
	};

	log("\n\n\n\nUsing default and delete safegaurd against subtle refactor bugs");

	//------------------------------------------
	class Prerefactor_worksfine
	{
		std::unordered_map<std::string, std::string> large_hashmap; //we don't want to copy this when we can move it.
	};
	// \/            \/             \/
	class Postrefactor_bug_movesdeleted
	{
		std::unordered_map<std::string, std::string> large_hashmap; //we don't want to copy this when we can move it.
	public:
		//this line deletes the cpp11 special member functions; what's worse -- this compiles. it translates all the mvoes to copys!!!
		~Postrefactor_bug_movesdeleted() { log("induced logging in dtor, we just accidentally deleted the default move ctors! Now we're going to do unnecessary copies when we could do moves"); }
	};

	//best practice is to provide default for these operations
	class RefactorSafeClass
	{
		std::unordered_map<std::string, std::string> large_hashmap; //we don't want to copy this when we can move it.
	public:
		RefactorSafeClass() = default;

		//by specifying these as default, we don't risk losing silently move functionality with refactors!
		~RefactorSafeClass() = default;
		RefactorSafeClass(const RefactorSafeClass& copy) = default;
		RefactorSafeClass& operator=(const RefactorSafeClass& copy) = default;
		RefactorSafeClass(RefactorSafeClass&& move) = default;
		RefactorSafeClass& operator=(RefactorSafeClass&& move) = default;
	};

	//-------------------------------------------
	special_case();

	std::cin.get();
}

//Caveat rule: there's no special rules involved if a template function accidently evalutes to a special member function
class EsotericCaveat
{
	//int *buffer = nullptr;
	FiveRule data;

public:
	//the below two functions may evalute to a copy ctor or the copy operator=
	template <typename T>
	EsotericCaveat(const T& param) {} //conventionally this would remove move ctor

	template <typename T>
	EsotericCaveat& operator=(const T& param) { log("operator="); return *this; } //conventionally this would remove move ctor
	//however, by declaring these two functions we do not lose the default move operations
	
	bool operator==(EsotericCaveat& rhs)
	{
		return rhs.data.getBuffer() == this->data.getBuffer();
	}
};

void special_case()
{
	log("\n\n\n\nSpecial Case");
	//force the template method to be instantiated
	EsotericCaveat force1{ nullptr }; //passing nullptr into ref, no compile errors!
	EsotericCaveat force2{ nullptr };
	force2 = force1; //this makes sure that the template method is instantiated by compiler
	EsotericCaveat force3(force1); //copy ctor instantiation


	int x = 5;
	EsotericCaveat ec1{x};

	//see if default move ctor operation actually moves buffer pointer
	EsotericCaveat ec2{ std::move(ec1) };

	if (ec2 == ec1)
	{
		log("data not moved, move ctor gone");
	}
	else
	{
		log("data moved! move ctor still exists");
	}

	x = 6;
}