
void A_foo();
void B_foo();

namespace
{
	int true_main()
	{
		//this calls has its own include of the template function
		A_foo();

		//this call also include the template function
		B_foo();

		//if the above share the same code body, the output should be 2 calls.
		//if each template gets a different instantiation, they will both print 1

		//output is 2!
		return 0;
	}
}

//int main()
//{
//	true_main();
//}