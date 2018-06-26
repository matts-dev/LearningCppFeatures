#pragma once
#include "Base_Pimpl.h"
#include <memory>
class Child_Pimpl : public Base_Pimpl
{
private:
	struct Implementation;
	std::unique_ptr<Implementation> pimpl;
public:
	Child_Pimpl();
	virtual ~Child_Pimpl();

	virtual void publicVirtualMethod() override;
protected:
	virtual void protectedVirtualMethod() override;
};

