import time
from infrared import infrared
from ultrasound import ultrasound
from output import output

# Instantiate the Dog object
ir = infrared(20, 15, 8)
us = ultrasound(15, 8)

test = ir.check()
test2 = us.check()
print(test)
print(test2)

