#ifndef __DAMERGER_GrapeTSScanner_HPP__
#define __DAMERGER_GrapeTSScanner_HPP__

#include "TSScannerBase.hpp"
#include "GrapeData.hpp"

/** timestamp scanner class for Gretina DAQ events **/
class GrapeTSScanner : public TSScannerBase<GrapeData>
{
public:
	const static std::string kMsgPrefix;
	GrapeTSScanner() {}
	~GrapeTSScanner() {}
	void SetReader();
	virtual Bool_t IsInGate();

protected:
	ULong64_t GetTS() const
	{
		if (!tree_data_)
			throw kMsgPrefix + "In GetTS(), tree_data_ is null";
		if (!tree_data_->Get())
			throw kMsgPrefix + "In GetTS(), tree_data_->Get() returned null";
		return tree_data_->Get()->GetTimestamp();
	}
};

#endif /* __DAMERGER_GrapeTSScanner_HPP__ */