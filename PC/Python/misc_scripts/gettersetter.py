class myclass:
    def __init__(self, a=None, b=None):
        self._a = a if a else 0
        self._b = b if b else 0
    
    def get_a(self):
        return self._a

    def set_a(self, a):
        self._a = a

    def get_b(self):
        return self._b

    def set_b(self, b):
        self._b = b


obj = myclass(1,10)
print('obj.a:', obj.a, '\nobj.b:', obj.b)