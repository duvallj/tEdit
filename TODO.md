All the things I would like to do, in order of priority:
 1. add debugging constraint invariant checks to all the files
    a. hopefully this will help me figure out what causes all the crashes
 2. Make it so the file is actually written from the real top, not just the
    screen's top (this was a huge oversight and I don't know how I missed that)
 3. change from linked list of raw strings to linked list of gap buffers? idk
    i'll have to check how that works for keeping the cursor's place in line
 4. allow you to create new files in the file browser
 5. change the tick delay to work off of real time as opposed to screen draw 
    time maybe? idk there should be a POSIX api for it tho
