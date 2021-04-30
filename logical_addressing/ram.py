RAM_SIZE = 1024


class RAM:
    def __init__(self, size=RAM_SIZE):
        self._minAddr = 0
        self._maxAddr = RAM_SIZE - 1
        self._memory = []   # a list of values.  Could be #s or instructions.
        for i in range(size):
            self._memory.append(0)

    def __getitem__(self, addr):
        return self._memory[addr]

    def __setitem__(self, addr, val):
        self._memory[addr] = val

    def is_legal_addr(self, addr):
        return self._minAddr <= addr <= self._maxAddr


class MMU:
    def __init__(self, RAM):
        self._ram = RAM
        self._reloc_reg = 0
        self._limit_reg = 0

    def __getval__(self, addr):
        return self._ram.__getitem__(addr)

    def __setval__(self, addr, value):
        self._ram.__setitem__(addr, value)

    def set_reloc_register(self, reg): #value of the smallest physcial address
        self._reloc_reg = reg

    def set_limit_register(self, lim): #the range of logical addresses (must fall within the range specified by the limit register)
        self._limit_reg = lim
    
    def addressCheck(self, addr):
        if addr >= self._limit_reg:
            print("BAD ADDRESS %d: too high", addr)
        return self._ram.__getitem__(addr + self._reloc_reg)

    def addressTranslation(self, addr, value):
        if addr >= self._limit_reg:
            print("BAD ADDRESS %d: too high", addr)
        else:
            self._ram.__setitem__(addr + self._reloc_reg, value)
