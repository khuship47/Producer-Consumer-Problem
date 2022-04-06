# Producer-Consumer-Problem

## Information
* Name: Khushi patel
* Assignment: Producer-Consumer problem
* Date: 6th april 2022

## What to do?
* When the buffer is complete, the producer will wait.
* When there are no items in the buffer, the consumer will wait.

## Solution
* We use in and out integer variable in the shared memory to keep track of item produced and consumed.

## How to run?
* use this command in order to run the program in linux terminal
  ```
  gcc -Wall -o producer producer.c
  gcc -Wall -o consumer consumer.c
  ./producer & ./consumer &  
  ```

## sample example
  Produced product id: 0
  Waiting products to be consumed
  Produced product id: 1
  Waiting products to be consumed
  Consumed product id: 0
  Produced product id: 0
  Waiting products to be consumed
  Waiting products to be consumed
  Consumed product id: 1
  Consumed product id: 0
  Produced product id: 1
  Produced product id: 0
  Waiting products to be consumed
  Consumed product id: 1
  .
  .
  .

