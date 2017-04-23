//
//  ofxChainableSetting.h
//
//  Created by ISHII 2bit on 2017/04/23.
//
//

#pragma once

#define ofxChainableSetting_is_loaded

#include "detail/chainable_setting.hpp"

template <typename this_type>
using ofxChainableSetting = bbb::chainable_setting<this_type>;
