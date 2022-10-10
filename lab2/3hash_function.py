def hash_function(input_string):
    k = 31
    mod = 1e9+7
    result = 0
    for i in input_string:
        result = int((result * k + ord(i)) % mod)
    return result


s1 = 'hello, world!'
s2 = 'Hello, world!'
print(hash_function(s1))
print(hash_function(s2))

