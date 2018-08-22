#include<iostream>
#include<string>


template<typename T>
void template_function_value(T obj);

template<typename T>
void template_function_ref(T& obj);

template<typename T>
void template_function_ptr(T* obj);

template<typename T>
void template_function_const_ref(const T& obj);

template<typename T>
void template_function_const_ptr(const T* obj);

template<typename T>
T rvalue_template (T&& param);

template<typename T, std::size_t N>
constexpr void print_array_size(T(&)[N]) noexcept; //this is a weird syntax, but it is A reference to a array of size N (T[N]&) doesn't compile -- it also doesn't compile with an actual passed argument

void print_lines();

static int main_v()
{
	//NOTE: I highly recommend mousing over function name in visual studio to see deduced parameter types.
	// the print methods within the functions do not reflect the fully qualified parameter type in some cases.

	int val = 5;
	template_function_value(val);		 //param: int			type: int
	template_function_ref(val);			 //param: int&			type: int
	template_function_ptr(&val);		 //param: int*			type: int
	template_function_const_ref(val);	 //param: const int&    type: int
	template_function_const_ptr(&val);	 //param: const int*	type: int
	print_lines();

	//pass-by-value drops const, volatile, and reference
	const int& cref = val;
	template_function_value(cref); //type is just int, not const int&; since we're making a copy the compile decides const and ref(&) are unneccessary 
	print_lines();

	double d = 1.0;
	const double cd = d;
	const double& cd_ref = d;
	std::cout << "Scenario1: parameter type is reference or a pointer" << std::endl;
	template_function_value(cd);      //param: double			type: double			//by value loses its constness since it creates a copy
	//notice that the parameter type becomes const on mouse over, this is needed for appropriate template instantiation
	template_function_ref(cd);		 //param: const double&    type: const double                  runtime printout omits const, but const is there because compiler enforces non-changes.
	template_function_ptr(&cd);      //param: const double*    type: const double
	template_function_const_ref(cd); //param: const double&    !!type: double!!							const const becomes just const; param type: const double& obj
	print_lines();


	std::cout << "Scenario2: parameter type is rvalue reference (universal reference)" << std::endl;
	rvalue_template(val); //param deduced to int&
	rvalue_template(cd);  //param deduced to const double& //the rules from ref section apply, but only after it is transformed from && to &
	rvalue_template(5);   //param deduced to int&&		//the rules above second apply to this version without any transformations (ie && to &)
	print_lines();

	std::cout << "Scenario2: parameter type is passed by value" << std::endl;
	template_function_value(cd); //passing by value just ignore const qualifiers, since we're making a copy, compilers just assume to make this modifiable 
	print_lines();

	//passing arrays
	int arr[5];
	template_function_value(arr); //decays to int ptr	param: int*			 type: int*
	template_function_ref(arr); //preserves size!		param: int(&obj)[5]	 type: int[5]
	template_function_ptr(arr); //decays to int ptr		param: int*			 type: int
	print_array_size(arr);
	print_lines();

	//for consistency, check out template deductions to function pointers
	void(*fptr)() = &print_lines;
	template_function_value(fptr);	//	param: void(*obj)()		type: void(*)()
	template_function_ptr(fptr);	//	param: void(*)()		type: void()	
	template_function_ref(fptr);	//	param: void(*&obj)()	type: void(*)()              //you can pass reference to function pointers!

	std::cin.get();
}


template<typename T>
void template_function_value(T obj)
{
	//two types are deduced!
	std::cout << "pass by value " << std::endl;
	std::cout << "typename: " << typeid(T).name() << std::endl;
	std::cout << "param: " << typeid(obj).name() << std::endl << std::endl;
}

template<typename T>
void template_function_ref(T& obj)
{
	//two types are deduced!
	std::cout << "pass by reference" << std::endl;
	std::cout << "typename: " << typeid(T).name() << std::endl;
	std::cout << "param: " << typeid(obj).name() << std::endl << std::endl;
}

template<typename T>
void template_function_ptr(T* obj)
{
	//two types are deduced!
	std::cout << "pass by pointer" << std::endl;
	std::cout << "typename: " << typeid(T).name() << std::endl;
	std::cout << "param: " << typeid(obj).name() << std::endl << std::endl;
}

template<typename T>
void template_function_const_ref(const T& obj)
{
	//two types are deduced!
	std::cout << "pass by const reference" << std::endl;
	std::cout << "typename: " << typeid(T).name() << std::endl;
	std::cout << "param: " << typeid(obj).name() << std::endl << std::endl; //doesn't seem to print true type, at least, it ommits the const.
}

template<typename T>
void template_function_const_ptr(const T* obj)
{
	//two types are deduced!
	std::cout << "pass by pointer to const" << std::endl;
	std::cout << "typename: " << typeid(T).name() << std::endl;
	std::cout << "param: " << typeid(obj).name() << std::endl << std::endl;
}

template<typename T>
T rvalue_template(T&& obj)
{
	//passed lvalues will instantiate this template param as T&
	//triva: this is the only template deducation that results naturally in a reference 

	//two types are deduced!
	std::cout << "pass by pointer to const" << std::endl;
	std::cout << "typename: " << typeid(T).name() << std::endl;
	std::cout << "param: " << typeid(obj).name() << std::endl << std::endl;

	return obj;
}

template<typename T, std::size_t N>
constexpr void print_array_size(T(&)[N]) noexcept
{
	std::cout << "size: " << N << std::endl;
}

void print_lines() {
	std::string underscores = std::string(30, '_');
	//std::cout << std::endl << std::endl;
	std::cout << underscores << std::endl;
}