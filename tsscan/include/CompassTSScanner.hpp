#ifndef __DAMERGER_CompassTSScanner_HPP__
#define __DAMERGER_CompassTSScanner_HPP__

#include "TSScannerBase.hpp"

/** timestamp scanner class for Compass DAQ events **/
class CompassTSScanner : public TSScannerBase<ULong64_t>
{
public:
	const static std::string kMsgPrefix;
	CompassTSScanner() {}
	~CompassTSScanner() {}
	void SetReader();
	virtual Bool_t IsInGate();

protected:
	ULong64_t GetTS() const
	{
		if (!tree_data_)
			throw kMsgPrefix + "In GetTS(), tree_data_ is null";
		if (!tree_data_->Get())
			throw kMsgPrefix + "In GetTS(), tree_data_->Get() returned null";
		return *tree_data_->Get();
	}
};

#endif /* __DAMERGER_CompassTSScanner_HPP__ */