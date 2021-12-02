#ifndef VANDLE_MERGER_OUTPUTTREEDATA_HPP_
#define VANDLE_MERGER_OUTPUTTREEDATA_HPP_

#include <vector>

/**
 * @brief Output data class for TreeMerger
 * 		  class T object with a vector of class U object
 * 
 * @tparam T 
 * @tparam U 
 */
template <class T, class U>
class OutputTreeData
{
public:
	T input_;
	std::vector<U> output_vec_;

	OutputTreeData() {}
	OutputTreeData(const T *input_ptr)
	{
		input_ = *input_ptr;
	}
	/**
	 * @brief Construct a new Output Tree Data object
	 *        initialized with T obj
	 * 
	 * @param obj 
	 */
	OutputTreeData(const OutputTreeData<T, U> &obj)
	{
		input_ = obj.input_;
		output_vec_ = obj.output_vec_;
	}
	/**
	 * @brief Destroy the Output Tree Data object
	 * 
	 */
	virtual ~OutputTreeData() {}

	/**
	 * @brief Clear output_vec_
	 * 
	 */
	void Clear()
	{
		output_vec_.clear();
		//T::Clear();
	}
	//ClassDef(OutputTreeData, 5)
};

#endif /** VANDLE_MERGER_OUTPUTTREEDATA_HPP_ **/