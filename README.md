# philosophers

Validated on 27/07/2024

100/100

Time invested: around one week

Spent way too much time on this project, no way to fix helgrind's complaints. Let it complain so. We don't care.

Just know that "lock order violated" does not necassarily mean that there's a problem in your code. It's essentially a warning which tells you that if someone else puts your code in another program that uses the same mutex in your code, it might cause problem. 

### BUT the problem does not necessarily comes from your code. ###
