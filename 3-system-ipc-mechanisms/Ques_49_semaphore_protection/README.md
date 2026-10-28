Setup:
1. `gcc ../31_semaphore_create/create_semaphore.c -o create_semaphore` (or compile from that directory).
2. Initialize the binary semaphore with the same key convention as this lab: this lab uses `ftok(".", 'T')` for ticket reservation and `ftok(".", 'H')` for shared memory's key. For the ticket example, use the included setup source below to create a semaphore under key `'T'` and set it to 1. The generic Lab 31 program uses key `'M'`, so do not assume those keys are interchangeable.
3. Run `./init_ticket`, then run `./ticket_reservation` from multiple terminals/processes.
4. For shared memory, initialize a semaphore with key `'M'` (value 1) and run `./init_shared`; the writer expects semaphore key `'M'` and shared-memory key `'H'`.
5. For counting resources, create a counting semaphore with value 2, then run `./counting_resource SEMID` in several terminals. The command takes the numeric semaphore ID.

The following setup program creates and initializes a semaphore for the ticket program under key `'T'`:

Run all commands from this `32_semaphore_protection` directory so `ftok(".", key)` produces consistent keys. Cleanup accepts the key character: `./remove_semaphore T`, `./remove_semaphore M`, or `./remove_semaphore C`.
