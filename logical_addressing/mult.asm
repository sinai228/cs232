# Multiply two numbers, found in locations 10 and 11, leaving the result in location 12.
# Assumes this code is loaded at location 20.
# >>>
# Multiply two numbers, found in locations 32 and 33, leaving the result in location 34.
# Assumes this code is loaded at location 20.

__main: 0
mov 0 14
mov *12 reg2
jez reg2 11
mov *13 reg1
jez reg1 31
mov reg2 reg0
sub 1 reg1
jez reg1 10
add reg0 reg2
jmp 6
mov reg2 14
end

#requires that 3 bytes of data space be reserved after the code.
__data: 3

