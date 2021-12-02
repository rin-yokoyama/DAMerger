#ifndef __DAMERGER_HicariTSScanner_HPP__
#define __DAMERGER_HicariTSScanner_HPP__

#include "TSScannerBase.hpp"
#include "Trace.hh"

/** timestamp scanner class for Gretina DAQ events **/
class HicariTSScanner : public TSScannerBase<Mode3Event>
{
public:
	const static std::string kMsgPrefix;
	HicariTSScanner() {}
	~HicariTSScanner() {}
	void SetReader();
	virtual Bool_t IsInGate();

protected:
	ULong64_t GetTS() const
	{
		if (!tree_data_)
			throw kMsgPrefix + "In GetTS(), tree_data_ is null";
		if (!tree_data_->Get())
			throw kMsgPrefix + "In GetTS(), tree_data_->Get() returned null";
		auto hits = *tree_data_->Get()->GetHit();
		for (auto const hit : hits)
		{
			auto hole = hit->GetTrace(0)->GetHole();
			auto crystal = hit->GetTrace(0)->GetCrystal();
			auto slot = hit->GetTrace(0)->GetSlot();
			auto chn = hit->GetTrace(0)->GetChn();
			if (hole == 11 && crystal == 0 && slot == 2 && chn == 9)
			{
				return hit->GetTS();
			}
		}
		return 0;
	}
};

#endif /* __DAMERGER_HicariTSScanner_HPP__ */