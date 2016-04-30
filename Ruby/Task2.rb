# m = Merge.new(c = MyCompare.new(:<)); c.count => 0
# m.merge([],[]) => []; c.count => 1
# m.merge([1],[2]) => [1,2]; c.count => 1
# m.merge([2],[1]) => [1,2]; c.count => 2
# m.merge([1,3,5],[7]) => [1,3,5,7]; c.count => 5
# m.merge([1,3,7,10],[4,5,8,9] => [1,3,4,5,7,8,10]

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

class Merge

	def initialize(comp)
		@compare = comp
	end

	def merge (a1, a2)

		result = Array.new
		a1.push(100000)
		a2.push(100000)

		i, j = 0
		while a1[i] != 100000 && a2[i] != 100000 do
			puts a1[i]
			puts a2[2]
			val = @compare.compare(a1[i], a2[j])
			if val == a1[i]
				result.push(a1[i])
				i = i + 1
			else
				result.push(a2[j])
				j = j + 1
			end
		end
		result
	end
end

m = Merge.new(MyCompare.new(':<'))

puts m.merge([], [])
puts m.merge([1], [2])
puts m.merge([3,8], [4,5,7])
