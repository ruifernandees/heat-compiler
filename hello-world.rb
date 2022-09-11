a = true

class A
  def if?
    return "YURI"
  end
end 

instance = A.new
name = instance.if?

# b= "TRUE" : "FALSE"
# puts b
puts name