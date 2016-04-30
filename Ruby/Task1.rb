# (c = MyCompare.new(:<)).count => 0
# c.compare(3,4) => true
# c.count => 1
# c.compare(4,2) => false
# c.count => 2
# MyCompare.new(:<).count => 0
# c.count => 2

class MyCompare
	attr_accessor :count
	def initialize(op)
		@operator = op
		@count = 0
	end
	def compare(val1, val2)
		if @operator == ':<'
			result = val1 < val2 ? true : false
		end
		if @operator == ':>'
			result = val1 > val2 ? true : false
		end
		@count = @count + 1
		result
	end
end

c = MyCompare.new(':<')
puts c.compare(3,4)
puts c.count
puts c.compare(4,2)
puts c.count
c = MyCompare.new(':<')
puts c.count
