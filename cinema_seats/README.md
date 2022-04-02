# Movie ticket race

5 people are trying to buy movie tickets, some seat choices overlap!

## WHO WILL GET THEIR SEATS?

Yep, it's a race (condition).

There are 5 seats left, all in a row.

G1, G2, G3, G4, G5.

Customer red1  wants G1, G2.
Customer green2  wants G4, G5
Customer blue3 wants G3, G4
Customer yellow4 wants G1, G2, G3
customer pink5 wants G2,G3,G4.
customer grey6 wants G2,G3

WHAT WILL HAPPEN!? 
1. Enforce in-order-buying by not using threads. Who gets what?
2. Feeding frenzy! Kick off all the threads in order from 1 to 6  and see who wins. Shouldn't it be the same? SHOULD IT THOUGH?
3. Delayed feeding frenzy! Make them all wait exactly 1000ms, then see who wins. WHY ISN'T ANYTHING WORKING?

Threads don't honour the order they start in, because they're all independent now and the operating system is treating them like life treats grownups - stuff just sort of happens because reasons and you try not to fall down.

Timers, now running in different threads, are getting different amounts of love from windows, even though you asked nicely for the same times.

Sleeping threads with `sleep_for` and chrono timings.

