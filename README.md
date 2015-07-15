Tribbler Server
=======

Introduction
-------
It's a Twitter-like system implemented using Apache Thrift RPCs.

>
>This code is part of [CSE223B SP13](http://cseweb.ucsd.edu/classes/sp13/cse223B-a/index.html "CSE223B SPRING 2013") (Distributed Computing and Systems) class at UC San Diego .
>This is a possible solution for [LAB3](http://cseweb.ucsd.edu/classes/sp13/cse223B-a/lab3.html "CSE223B LAB 3")
>

Overview
-------
The whole system is composed of:
* **Client**: It is just like Twitters web service. It just allows users to login, send messages, read subscriptions
* **Tribbler Server**: This server implements the application logic that makes Tribbler work. All commands from the client are processed here. This is the layer responsible of implementing functions as "subscribe to", "post", "create user", etc...
* **Storage System**: Here implemented as a key-value storage service (much like a hash table). This were all information from Tribbler server is stored.




[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/danilogr/tribbler/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

