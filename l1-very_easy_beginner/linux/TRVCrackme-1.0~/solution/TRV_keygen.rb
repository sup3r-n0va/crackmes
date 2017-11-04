puts "Enter your name:"
username = gets()
sum = 0
username.scan(/./).each do |c|
  sum += c.upcase.ord
end

puts "Your serial:"
puts (sum ^ 0x3421 ^ 0x5786)
