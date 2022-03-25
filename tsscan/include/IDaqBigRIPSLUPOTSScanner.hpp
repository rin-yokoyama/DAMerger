#ifndef __DAMERGER_IDaqBigRIPSLUPOTSSCanner_HPP__
#define __DAMERGER_IDaqBigRIPSLUPOTSSCanner_HPP__

#include "TSScannerBase.hpp"
#include "IDaqData.hpp"

/** timestamp scanner class for Isobe DAQ events **/
class IDaqBigRIPSLUPOTSSCanner : public TSScannerBase<IDaqData>
{
public:
	const static std::string kMsgPrefix;
	IDaqBigRIPSLUPOTSSCanner() {}
	~IDaqBigRIPSLUPOTSSCanner() {}
	void SetReader();
	virtual Bool_t IsInGate();

protected:
	ULong64_t GetTS() const
	{
		if (!tree_data_)
			throw kMsgPrefix + "In GetTS(), tree_data_ is null";
		if (!tree_data_->Get())
			throw kMsgPrefix + "In GetTS(), tree_data_->Get() returned null";
		return tree_data_->Get()->GetBigRIPSLUPOTimestamp();
	}
};

#endif /* __DAMERGER_IDaqBigRIPSLUPOTSSCanner_HPP__ */