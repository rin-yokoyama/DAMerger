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
		compass_lupo_ts_ = obj.compass_lupo_ts_;
		brips_lupo_ts_ = obj.brips_lupo_ts_;
		myriad_ts_ = obj.myriad_ts_;
		event_id_ = obj.event_id_;
	}
	/**
	 * @brief Destroy the IDaqData object
	 *
	 */
	virtual ~IDaqData() {}

	/**
	 * @brief Set the Timestamps object
	 *
	 * @param compass Compass LUPO timestamp
	 * @param brips BigRIPS LUPO timestamp
	 * @param myriad MYRIAD timestamp
	 */
	void SetTimestamps(const ULong64_t &compass, const ULong64_t &brips, const ULong64_t &myriad, const ULong64_t &evt)
	{
		compass_lupo_ts_ = compass;
		brips_lupo_ts_ = brips;
		myriad_ts_ = myriad;
		event_id_ = evt;
	}

	/**
	 * @brief Get Compass LUPO Timestamp
	 *
	 * @return ULong64_t timestamp
	 */
	ULong64_t GetCompassLUPOTimestamp() const { return compass_lupo_ts_; }
	/**
	 * @brief Get BigRIPS LUPO Timestamp
	 *
	 * @return ULong64_t timestamp
	 */
	ULong64_t GetBigRIPSLUPOTimestamp() const { return brips_lupo_ts_; }
	/**
	 * @brief Get MYRIAD Timestamp
	 *
	 * @return ULong64_t timestamp
	 */
	ULong64_t GetMYRIADTimestamp() const { return myriad_ts_; }
	/**
	 * @brief Get Event ID
	 *
	 * @return ULong64_t Event ID
	 */
	ULong64_t GetEventID() const { return event_id_; }

private:
	ULong64_t compass_lupo_ts_; /// LUPO timestamp for compass
	ULong64_t brips_lupo_ts_;	/// LUPO timestamp for bigrips
	ULong64_t myriad_ts_;		/// MYRIAD timestamp
	ULong64_t event_id_;		/// Event ID

	ClassDef(IDaqData, 3)
};

#endif /// __DAMERGER_IDAQ_DATA_HPP__