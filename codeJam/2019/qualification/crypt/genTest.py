

import itertools as it
import random

def primeGenErat3(minBound, maxBound):
    D = { 9: 3, 25: 5 }
    if minBound <= 2:
        yield 2
    if minBound <= 3:
        yield 3
    if minBound <= 5:
        yield 5
    MASK= 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0,
    MODULOS= frozenset( (1, 7, 11, 13, 17, 19, 23, 29) )

    for q in it.compress(
            it.islice(it.count(7), 0, None, 2),
            it.cycle(MASK)):
        p = D.pop(q, None)
        if p is None:
            D[q*q] = q
            if q >= minBound:
                yield q
        else:
            x = q + 2*p
            while x in D or (x%30) not in MODULOS:
                x += 2*p
            D[x] = p
        if q > maxBound:
            return

minBound = 101
maxBound = 10000
numTests = 100
print numTests

primes = []
for prime in primeGenErat3(minBound, maxBound):
    primes.append(prime)

for test in range(numTests):
    alphIndexes = set()
    while len(alphIndexes) < 26:
        alphIndexes.add(random.randrange(0,len(primes),1))

    alphIndList = sorted(alphIndexes) #list of indexes to pull from prime list
    alphPrimesList = []
    for i in alphIndList:
        alphPrimesList.append(primes[i]) # list of random primes, in order


    # list of indexes to pul from alphIndList
    indexList = range(26)
    indexList.extend(range(26))
    indexList.extend(range(26))
    random.shuffle(indexList)

    samplePrimeList = []
    alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    message = ''
    for i in indexList:
        samplePrimeList.append(alphPrimesList[i])
        message += alphabet[i]

    sampleProb = []
    for index in range(len(samplePrimeList)-1):
        sampleProb.append(samplePrimeList[index]*samplePrimeList[index+1])


    print '{} {}'.format(maxBound, len(indexList)-1)
    print ' '.join(map(str, sampleProb))



