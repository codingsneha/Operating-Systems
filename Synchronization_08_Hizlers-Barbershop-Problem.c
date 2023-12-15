/*
Hilzer’s Barbershop problem

Our barbershop has three chairs, three barbers, and a waiting
area that can accommodate four customers on a sofa and that has
standing room for additional customers. Fire codes limit the total
number of customers in the shop to 20.
A customer will not enter the shop if it is filled to capacity with
other customers. Once inside, the customer takes a seat on the sofa
or stands if the sofa is filled. When a barber is free, the customer
that has been on the sofa the longest is served and, if there are any
standing customers, the one that has been in the shop the longest
takes a seat on the sofa. When a customer’s haircut is finished,
any barber can accept payment, but because there is only one cash
register, payment is accepted for one customer at a time. The barbers divide their time among cutting hair, accepting payment, and
sleeping in their chair waiting for a customer.
In other words, the following synchronization constraints apply:
• Customers invoke the following functions in order: enterShop, sitOnSofa,
getHairCut, pay.
• Barbers invoke cutHair and acceptPayment.
• Customers cannot invoke enterShop if the shop is at capacity.
• If the sofa is full, an arriving customer cannot invoke sitOnSofa.
• When a customer invokes getHairCut there should be a corresponding
barber executing cutHair concurrently, and vice versa.
• It should be possible for up to three customers to execute getHairCut
concurrently, and up to three barbers to execute cutHair concurrently.
• The customer has to pay before the barber can acceptPayment.
• The barber must acceptPayment before the customer can exit.


Here are the variables I used in my solution:
Hilzer’s barbershop hint
1 n = 20
2 customers = 0
3 mutex = Semaphore (1)
4 sofa = Semaphore (4)
5 customer1 = Semaphore (0)
6 customer2 = Semaphore (0)
7 barber = Semaphore (0)
8 payment = Semaphore (0)
9 receipt = Semaphore (0)
10 queue1 = []
11 queue2 = []
mutex protects customers, which keeps track of the number of customers
in the shop, and queue1 which is a list of semaphores for threads waiting for a
seat on the sofa.
mutex2 protects queue2, which is a list of semaphores for threads waiting
for a chair.
sofa is a multiplex that enforces the maximum number of customers on the
sofa.
customer1 signals that there is a customer in queue1, and customer2 signals
that there is a customer in queue2.
payment signals that a customer has paid, and receipt sigmals that a barber
has accepted payment.


Hilzer’s barbershop solution (customer)
1 self . sem1 = Semaphore (0)
2 self . sem2 = Semaphore (0)
3
4 mutex . wait ()
5 if customers == n :
6 mutex . signal ()
7 balk ()
8 customers += 1
9 queue1 . append ( self . sem1 )
10 mutex . signal ()
11
12 # enterShop ()
13 customer1 . signal ()
14 self . sem1 . wait ()
15
16 sofa . wait ()
17 # sitOnSofa ()
18 self . sem1 . signal ()
19 mutex . wait ()
20 queue2 . append ( self . sem2 )
21 mutex . signal ()
22 customer2 . signal ()
23 self . sem2 . wait ()
24 sofa . signal ()
25
26 # sitInBarberChair ()
27
28 # pay ()
29 payment . signal ()
30 receipt . wait ()
31
32 mutex . wait ()
33 customers -= 1
34 mutex . signal ()


Hilzer’s barbershop solution (barber)
1 customer1 . wait ()
2 mutex . wait ()
3 sem = queue1 . pop (0)
4 sem . signal ()
5 sem . wait ()
6 mutex . signal ()
7 sem . signal ()
8
9 customer2 . wait ()
10 mutex . wait ()
11 sem = queue2 . pop (0)
12 mutex . signal ()
13 sem . signal ()
14
15 barber . signal ()
16 # cutHair ()
17
18 payment . wait ()
19 # acceptPayment ()
20 receipt . signal ()

*/