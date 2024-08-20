# philosophers

Validated on 27/07/2024

100/100

Time invested: about one week

Lock Order Violated means that in this program, the mutexs are not always locked in the same order, hence a deadlock might appear (but the setting of this philosopher project will not actually let it happen). This should not be a problem for this project if your code is well written.

Error explanation:

When you lock multiple mutexes in different threads, there should be a consistent order in which these locks are acquired. If thread A locks mutex M1 and then mutex M2, but thread B locks mutex M2 first and then tries to lock M1, you have a situation where both threads could end up waiting for each other, leading to a deadlock.

(Reversing the order of taking up forks for the last philo and setting a little delay (mandatory thinking time) for all philos of odd index should fix this helgrind warning if you do want a "perfect" philosopher for certain reasons)
