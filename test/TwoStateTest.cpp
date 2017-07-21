//
// @brief   
// @details 
// @author  Steffen Peikert (ch3ll)
// @email   n3m3s1s.games+dev@gmail.com
// @version 1.0.0
// @date    19.07.2017 23:59
// @project CodeCollection
//

#include <catch.hpp>
#include "codecollection/TwoState/TwoState.hpp"

using namespace TWOSTATE;

TEST_CASE("Twostate capacity constructor test.")
{
	const int NUM_TEST_VALUES = 10;


	TwoStateArray<int> t = TwoStateArray<int>(NUM_TEST_VALUES);

	for(unsigned int i = 0; i < NUM_TEST_VALUES; i++)
	{
		CHECK(t[i] == int());
		CHECK(t.IsLow(i));
		CHECK_FALSE(t.IsHigh(i));
	}

	CHECK(t.Capacity == NUM_TEST_VALUES);
}