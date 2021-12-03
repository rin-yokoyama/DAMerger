/**
 * @file GrapeData.hpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief Output data container for Grape
 * @version 0.1
 * @date 2021-12-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __DAMERGER_GrapeData_HPP__
#define __DAMERGER_GrapeData_HPP__
#include "TObject.h"

class GrapeData : public TObject
{
public:
	/**
	 * @brief Default constructor
	 * 
	 */
	GrapeData() : TObject(), has_idaq_ts_(false), ts_(0) {}
	/**
	 * @brief Copy constructor
	 * 
	 * @param obj 
	 */
	GrapeData(const GrapeData &obj) : TObject(obj)
	{
		has_idaq_ts_ = obj.has_idaq_ts_;
		ts_ = obj.ts_;
	}
	/**
	 * @brief Destroy the GrapeData object
	 * 
	 */
	virtual ~GrapeData() {}

	/**
	 * @brief Set the Timestamps object.
	 *        It sets the has_idaq_ts_ flag to true.
	 * @param ts MYRIAD timestamp
	 */
	void SetTimestamp(const ULong64_t &ts)
	{
		has_idaq_ts_ = true;
		ts_ = ts;
	}

	/**
	 * @brief Get has_idaq_ts_ flag
	 * 
	 * @return Bool_t has_idaq_ts_
	 */
	Bool_t GetHasIDaqTS() const { return has_idaq_ts_; }
	/**
	 * @brief Get MYRIAD Timestamp
	 * 
	 * @return ULong64_t timestamp
	 */
	ULong64_t GetTimestamp() const { return ts_; }

private:
	Bool_t has_idaq_ts_; /// flag if this event has Isobe DAQ trigger
	ULong64_t ts_;		 /// MYRIAD timestamp

	ClassDef(GrapeData, 1)
};

#endif /// __DAMERGER_Grape_Data_HPP__