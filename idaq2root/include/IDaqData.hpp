/**
 * @file IDaqData.hpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief Output data container for Isobe DAQ
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __DAMERGER_IDAQDATA_HPP__
#define __DAMERGER_IDAQDATA_HPP__
#include "TObject.h"

class IDaqData : public TObject
{
public:
	/**
	 * @brief Default constructor
	 * 
	 */
	IDaqData() : TObject() {}
	/**
	 * @brief Copy constructor
	 * 
	 * @param obj 
	 */
	IDaqData(const IDaqData &obj) : TObject(obj)
	{
		lupo_ts_ = obj.lupo_ts_;
		myriad_ts_ = obj.myriad_ts_;
	}
	/**
	 * @brief Destroy the IDaqData object
	 * 
	 */
	virtual ~IDaqData() {}

	/**
	 * @brief Set the Timestamps object
	 * 
	 * @param lupo LUPO timestamp
	 * @param myriad MYRIAD timestamp
	 */
	void SetTimestamps(const ULong64_t &lupo, const ULong64_t &myriad)
	{
		lupo_ts_ = lupo;
		myriad_ts_ = myriad;
	}

	/**
	 * @brief Get LUPO Timestamp
	 * 
	 * @return ULong64_t timestamp
	 */
	ULong64_t GetLUPOTimestamp() const { return lupo_ts_; }
	/**
	 * @brief Get MYRIAD Timestamp
	 * 
	 * @return ULong64_t timestamp
	 */
	ULong64_t GetMYRIADTimestamp() const { return myriad_ts_; }

private:
	ULong64_t lupo_ts_;	  /// LUPO timestamp
	ULong64_t myriad_ts_; /// MYRIAD timestamp

	ClassDef(IDaqData, 1)
};

#endif /// __DAMERGER_IDAQ_DATA_HPP__