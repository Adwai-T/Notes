# RxJs

* From event

Create an observable from an event like `mousemove`

* Hot Observable

Thye starts reciving emittered data from the time that it subscribes and will not recieve data that the observeable has already emitted.

* *Cold* will revieve all data from begining.

*Cold observable* can be converted to hot by using `share` operator from rxjs library.

* Subject

It is a observable and observer at the same time.

* BehaviourSubject

It stores the last value that was emitter and this last stored value will be emitted by any subscibers.

* ReplaySubject

Replay subject is a superset of BehaviourSubject that it allows us to specify the number of event values that it stores and are dipatched to any subscriber that subscribe to it later. We pass in the buffer size that will store the number of event emitter previously.

* Async Subject

only emits the last value. For this to work we have to call the complete on our subscriber.

* Operators

map, merge, skipuntil
