#include <memory>
#include <string>
#include <vector>
#include<iostream>



namespace
{
	class RemoveCopies
	{
	public:
		RemoveCopies() = default;
		RemoveCopies(const RemoveCopies& copy) = delete;
		RemoveCopies& operator=(const RemoveCopies& copy) = delete;
	};

	class RemoveMoves
	{
	public:
		RemoveMoves() = default;
		RemoveMoves(RemoveMoves&& move) = delete;
		RemoveMoves& operator=(RemoveMoves&& move) = delete;
	};

	struct Shape
	{
		std::string name{ "matt" };
	};

	struct Element
	{
		std::unique_ptr<Shape> person;
	};

	struct ElementNode
	{
		ElementNode(Element& inElement) : data(inElement) {}

		Element& data;
	};

	struct ElementEntry : public RemoveMoves, public RemoveCopies
	{
		std::shared_ptr<ElementNode> sp_data;
	};

	struct MyObject
	{
		std::unique_ptr<ElementEntry> up_data;
	};


	void true_main()
	{
		Element datum;
		datum.person = std::make_unique<Shape>();

		auto sp_datanode = std::make_shared<ElementNode>(datum);

		MyObject from;
		from.up_data = std::make_unique<ElementEntry>();
		from.up_data->sp_data = sp_datanode;
		MyObject to(std::move(from));

		//------------------------------------
		std::vector<MyObject> objs;
		objs.push_back({});
		objs[0].up_data = std::make_unique<ElementEntry>();
		objs[0].up_data->sp_data = sp_datanode; 
		
		objs.push_back(MyObject{});//push a blank object and cause buffer exapnsion
		std::cout << "buffer expanded, break here to inspect contents" << std::endl;
	}
}

//int main()
//{
//	true_main();
//}