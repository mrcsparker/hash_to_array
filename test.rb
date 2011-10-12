require 'hash_to_array'

h = { 
  :outer_key => { :inner_key => "inner text" }, 
  :other_outer_key => "outer text",
  :start_nesting => { :nesting_1 => { :nesting_2 => { :nesting_3 => "nesting 3 value" }}},
  :last_item => "last item value"
}

hash_to_array = HashToArray.new
p hash_to_array.all_keys(h)
p hash_to_array.all_values(h)
