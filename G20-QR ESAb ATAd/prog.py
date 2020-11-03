# python3.5
# Cannot use f"bla {blubb}" stirng interpolation syntax

import sys

def fprint(*args,**kwargs):
    print(*args,**kwargs)
    sys.stdout.flush()

debug = sys.argv[1] == "-v" if len(sys.argv) >= 2 else False

def dprint(*args,**kwargs):
    if debug:
        fprint(*args,file=sys.stderr,**kwargs)

"""
bit 0 | 1  <->  arr = -1 | 1
bit unknown <-> arr = 0
"""

noop = 0
rev = 1
inv = 2
revinv = 3
ops = [
    lambda a: a, # 0 noop
    lambda a: a[::-1], # 1 reverse
    lambda a: [-x for x in a], # 2 invert
    lambda a: [-x for x in a][::-1], # 3 invert and reverse
]

def b2a(b):
    return b*2 - 1

def a2b(a):
    return (a+1)//2

def aknown(a):
    return a != 0

def aflip(a):
    return -a

def arr2bit(arr):
    return [a2b(a) for a in arr]

def bit2arr(bit):
    return [b2a(b) for b in bit]


def indexOfFirst(pred, xs):
    iz = None
    for i, _ in enumerate(xs):
        if pred(i):
            return i
    return None

class Solver:

    def __init__(self, t, B):
        self.t = t
        self.B = B
        self.nq = 0 # number of queries made
        self.arr = [0] * B
        self.recovered = True

    def count_query(self):
        self.nq = self.nq + 1

    def query_index_a(self,i): # i is zero-based. returns bit at index i
        dprint("querying {}".format(i+1))
        fprint(i+1) # queries are 1 based
        self.count_query()
        return b2a(int(input()))

    def learnbit(self):
        learnables = list(filter(lambda t: t[1] == 0, zip(range(B),self.arr)))
        if len(learnables) == 0:
            return True
        else:

            (i,_) = sorted(learnables,key=lambda t: min(t[0],B-1-t[0]))[0]
            b = self.query_index_a(i)

            if b in [-1,1]:
                dprint("Found i={} abit {}".format(i,b))
                self.arr[i] = b
            else:
                dprint("Invalid returned abit: {}".format(b)); exit(0)

            return len(learnables) == 1 # True iff we learned the last bit

    # detects and corrects operation {op} at index {i} and it's opposite
    def detect_correct(self,i,op):
        j = B-1-i
        dprint("detect_correct {} {}".format(i,op))
        if op == inv:
            bi = self.query_index_a(i)
            if bi != self.arr[i]:  # changed. apply inversion
                self.arr = ops[inv](self.arr)
                dprint("Detected INVERSION")
        elif op == rev:
            bi = self.query_index_a(i)
            if bi != self.arr[i]: # changed. apply reversal
                self.arr = ops[rev](self.arr)
                dprint("DETECTED  REVERSAL")


    def forget_half_known_pairs(self):
        self.arr = [self.arr[i] if aknown(self.arr[i]) and aknown(self.arr[B-1-i])
                    else 0
                    for i in range(B)]
        dprint("Forgot half-known pairs {}".format(self.arr))

    def recover(self):
        # We try to find two pair of opposing positions with each equal and unequal value.
        # There are four cases.

        self.forget_half_known_pairs() # makes pairs in self.arr unknown
        # where one of the pair is unknown

        ieq = indexOfFirst(
            lambda i: aknown(self.arr[i])
                and self.arr[i] == self.arr[B-1-i],
            self.arr)

        idf = indexOfFirst(
            lambda i: aknown(self.arr[i])
                and self.arr[i] == aflip(self.arr[B-1-i]),
            self.arr)

        dprint("ieq {}, idf {}".format(ieq,idf))

        # use count_query()
        if ieq is not None and idf is not None:
            # use == to detect and correct inversion
            # then, use != to detect and correct reversal
            self.detect_correct(ieq,inv)
            self.detect_correct(idf,rev)

        elif ieq is not None and idf is None:
            # use == to detect and correct inversion
            self.detect_correct(ieq, inv)

        elif ieq is None and idf is not None:
            """
            array is reverse-inversion-invariant
            find whether noop, inversion or reversal was applied:
                001011
                    001011
                    110100
                    110100
            Due to the commutativity, inversion == reversal.
            Hence, we only check a single pair to see whether the array was changed or not.
            """
            self.detect_correct(idf,rev)
            pass

        elif ieq is None and idf is None: # nothing to do
            pass

        self.recovered = True
        return

    def guess(self):
        for b in arr2bit(self.arr): # print stored bits
            fprint(b,end="")
        fprint("")

        if input() != "Y": # check for response and continue if correct
            dprint("Wrong prediction for {}!".format(self.arr))
            exit(0)

    def solve(self):
        dprint("======= SOLVING =========")
        # repeatedly make queries to solve the problem
        while self.nq < 150:
            dprint("nq {} ; arr {}".format(self.nq,self.arr))

            # after every tenth query the database is randomized
            if self.nq > 0 and self.nq % 10 == 0:
                self.recovered = False

            if self.recovered:
                if self.learnbit(): # returns true if last bit was learned
                    self.guess()
                    return
            else:
                self.recover()

T, B = map(int,input().split(" "))

for t in range(T):
    Solver(t,B).solve()
