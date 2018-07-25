#pragma once
class InheritImpl
{
public:
	virtual ~InheritImpl() {}

	virtual void do_work() = 0;
};

InheritImpl* GetNewInstance();

