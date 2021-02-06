import re

test = '15st 2oz'
results = re.findall("[0-9]+", test)

    result = results[0] + '.' + results[1]
print(result)
