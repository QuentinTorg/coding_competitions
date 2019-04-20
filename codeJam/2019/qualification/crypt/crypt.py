# raw_input() reads a string with a line of input, stripping the '\n' (newline) at the end.
# This is all you need for most Kickstart problems.

def findPrimeFactors(val):
    if val % 2 == 0:
        return (2, val / 2)
    if val % 3 == 0:
        return (3, val / 3)

    j = 1

    plus = 0
    while plus * plus < val:
        minus = 6*j-1
        plus = 6*j+1
        if val % minus == 0:
            return (minus, val / minus)
        if val % plus == 0:
            return (plus, val / plus)
        j = j + 1


t = int(raw_input())  # read a line with a single integer

for i in xrange(1, t + 1):
    n, l = [int(s) for s in raw_input().split(" ")]  # read a list of integers, 2 in this case
    crypt = [int(s) for s in raw_input().split(" ")]  # read a list of integers, 2 in this case

    smallNum = min(crypt)
    smallInd = crypt.index(smallNum)

    factorStart = [0] * (smallInd + 1)
    factorEnd = [0] * (len(crypt) - smallInd)

    fact1, fact2 = findPrimeFactors(smallNum)

    if smallInd != 0:
        if crypt[smallInd - 1] % fact1 == 0:
            factorStart[-1] = fact1
            factorEnd[0]   = fact2
        else:
            factorStart[-1] = fact2
            factorEnd[0]   = fact1

        if smallInd > 1:
            for index in range(smallInd-1, -1, -1):
                factorStart[index] = crypt[index] / factorStart[index+1]
        else:
            factorStart[0] = crypt[0] / factorStart[1]

    else:
        if crypt[smallInd + 1] % fact2 == 0:
            factorStart[0] = fact1
            factorEnd[0]   = fact2
        else:
            factorStart[0] = fact2
            factorEnd[0]   = fact1

    if len(factorEnd) > 2:
        for factorInd, cryptInd in enumerate(range(smallInd+1, len(crypt)),1):
            factorEnd[factorInd] = crypt[cryptInd] / factorEnd[factorInd-1]
    elif len(factorEnd) > 1:
        factorEnd[1] = crypt[-1] / factorEnd[0]

    factorStart.extend(factorEnd)
    sortedFactors = sorted(set(factorStart))

    alph = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

    cipher = {}
    for index, letter in enumerate(alph):
        cipher[sortedFactors[index]] = letter

    message = 'Case #{}: '.format(i)
    for num in factorStart:
        message += cipher[num]


    print message
    # check out .format's specification for more formatting options
