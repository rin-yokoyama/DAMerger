#ifndef __DAMERGER_IDaqMyriadTSScanner_HPP__
#define __DAMERGER_IDaqMyriadTSScanner_HPP__

#include "TSScannerBase.hpp"
#include "IDaqData.hpp"

/** timestamp scanner class for Isobe DAQ events **/
class IDaqMyriadTSScanner : public TSScannerBase<IDaqData>
{
public:
	const static std::string kMsgPrefix;
	IDaqMyriadTSScanner() {}
	~IDaqMyriadTSScanner() {}
	void SetReader();
	virtual Bool_t IsInGate();

protected:
	ULong64_t GetTS() const
	{
		if (!tree_data_)
			throw kMsgPrefix + "In GetTS(), tree_data_ is null";
		if (!tree_data_->Get())
			throw kMsgPrefix + "In GetTS(), tree_data_->Get() returned null";
		return tree_data_->Get()->GetMYRIADTimestamp();
	}
};

#endif /* __DAMERGER_IDaqMyriadTSScanner_HPP__ */