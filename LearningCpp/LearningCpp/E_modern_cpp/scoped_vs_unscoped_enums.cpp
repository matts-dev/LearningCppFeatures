//NOTE: this file is designed to read from top to bottom
#include <iostream>
#include <tuple>
namespace
{
	void takes_size(size_t sz) { std::cout << sz << std::endl; }
}
static void part2(); //avoiding forward declaring in anyonomous namespaces because that's weird
static void part3();

int main()
{
	//unscoped enum
	enum Shapes2D { Square, Triangle, Circle };

	//scoped enum
	enum class Shapes3D { Cube, Pyramid, Sphere };

	//cpp98 style enum (the unscoped enum) pollutes the entire namespace for which it is defined,
	//you can use its name anywhere without scope resolution (ie scope::name)
	Shapes2D x1 = Square;
	Shapes2D x2 = Shapes2D::Square; //you can still scope it if you want to, but scope isn't required

	//Shapes3D y1 = Cube; //doesn't compile; identifier cube is underfined; ie we need to scope it!
	Shapes3D y2 = Shapes3D::Cube;

	//Because unscoped enums are present everywhere, the following won't compile
	//auto Triangle = 0; //error C2365 : 'main::Triangle' : redefinition; previous definition was 'enumerator'
	{
		auto Triangle = 0; //however this will compile on msvc, I guess because of shadowing.
	}

	//scoped enums don't conflict with types
	auto Cube = 0; //no conflict with Shapes3D::Cube

	// ---------------------------------------------------------------
	// Scoped enums allow implicit conversions, which can lead to bugs.
	Shapes2D tri = Triangle;
	if (tri) //implicit conversion to bool
	{	
		takes_size(tri); //implicitly converting to size_tz; if this were a typeo then the compiler wouldn't complain
	}
	Shapes3D pyr = Shapes3D::Pyramid;
	if (static_cast<bool>(pyr)) //must do cast for compile
	{
		takes_size(static_cast<size_t>(pyr)); //here wem ust also cast the type
	}

	// ----------------------------------------------------------------
	//The casts above worked because enums fall back to using hidden underlying types.

	//unscoped enums choose the smallest possible type that will work
	enum English { THE, A, TO}; //Probably falls back to a char, but may fall back to something else (like int) if compiler is opitmizing for speed, instead of size.

	enum class Spanish {EL, UN, A}; //Scoped enums default to int

	part2();
}

//enums can't (before cpp11) be forward declared
//The compiler can't know the size of the enum (even though it implements this size policy) (I guess theorteicall you may have a .h file and a binary library? no way to know what the compiler used? maybe?)
//enum Terrain; //forward declarations can't be used (msvc actually allows them though; but xcode's compiler will not compile!
//enum Terrain{ROCK, SAND, GRASS, DIRT};

//however, you can forward declare scoped enums! Because they have a known default type!
enum class Terrain_Scoped;	//forward declaration is possible because it knows it uses int!
enum class Terrain_Scoped { ROCK, SAND, GRASS, DIRT};

//There is 1 exception to forward declarations for unscoped enums, you can forward declare them if you specify a type
enum WaterBody_Unscoped : int; //unscoped enum forward declarations (note, I believe this was added only in c++11)
enum WaterBody_Unscoped : int {OCREAN, LAKE, POND, RIVER, CREEK, FORD};

enum class WaterBody_Scoped : int; //scoped enum declarations are fine too
enum class WaterBody_Scoped: int { OCREAN, LAKE, POND, RIVER, CREEK, FORD }; 

auto get_person() { return std::tuple<std::string, int, char>("Matt", 26, 'U'); } //cpp14 feature; not using decltype typededuction rules in this case; rather using template param rules
void part2()
{
	//scoped enums may be useful for tuple names
	enum TupleFields{NAME, AGE, NATIONALITY};
	std::tuple<std::string, int, char> person = get_person(); //avoiding using auto in this case for sake of readability
	auto age1 = std::get<1>(person); //hard to remember that 1 == age
	auto age2 = std::get<AGE>(person); //implicit conversion to size_t (the expected template type) is helpful here! No memorization needed.


	enum class TupleFields_Scoped : short { NAME, AGE, NATIONALITY };
	//we can do something similar with scoped, but it requires a cast.
	auto age3 = std::get<static_cast<size_t>(TupleFields_Scoped::AGE) >(person); //saves you from polluting namespace

	part3();
}

//the book points out you can reduce verbosity by using a function to convert the scoped enum,
//since things are done at compile time, it recommends a constexpr, then points out that it might as well be a generic function

//cpp11
template<typename T>
constexpr typename std::underlying_type<T>::type toIdx(T enum_val) noexcept
{
	//this is the static_cast from above example in age3, but we're doing it generically
	return static_cast<std::underlying_type<T>::type>(enum_val);
} 

//cpp14 traits
template<typename T>
constexpr std::underlying_type_t<T> toIdx_cpp14traits(T enum_val) noexcept
{
	return static_cast<std::underlying_type_t<T>>(enum_val);
}

//cpp14 traits and type deduction
template<typename T>
constexpr auto toIdx_cpp14_auto(T enum_val) noexcept
{
	return static_cast<std::underlying_type_t<T>>(enum_val);
}

static void part3()
{
	enum class TupleFields_Scoped : short { NAME, AGE, NATIONALITY };
	std::tuple<std::string, int, char> person = get_person(); //avoiding using auto in this case for sake of readability

	//we can do something similar with scoped, but it requires a cast.
	auto age4 = std::get<toIdx(TupleFields_Scoped::AGE)>(person);
	auto age5 = std::get<toIdx_cpp14traits(TupleFields_Scoped::AGE)>(person);
	auto age6 = std::get<toIdx_cpp14_auto(TupleFields_Scoped::AGE)>(person);
}