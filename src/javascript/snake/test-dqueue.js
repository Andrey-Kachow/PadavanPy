function cry(msg) {
  alert(msg)
  console.log(msg)
}

function assert(boolExpr, msg) {
  if (!boolExpr) {
    if (msg == null) {
      msg = "Something went wrong"
    }
    msg = `Fail! ${msg}`
    cry(msg)
  }
}

function assertEquals(actual, expected) {
  if (expected != actual) {
    cry(`Assertion error! Expected ${expected}, but got ${actual}`)
  }
}

function testQueueExhausted(q) {
  assert(q.isEmpty(), "q should be empty")

  q.add(1)

  assert(!q.isEmpty(), "q should not be empty")
  assertEquals(q.head().value, 1)
  assertEquals(q.tail().value, 1)

  q.add(2)
  q.add(3)

  assertEquals(q.head().value, 1)
  assertEquals(q.tail().value, 3)
  assertEquals(q.head().next.value, 2)
  assertEquals(q.tail().prev.value, 2)
  assertEquals(q.head().next.next.value, 3)
  assertEquals(q.tail().prev.prev.value, 1)

  assert(q.contains(1), "contains 1 check")
  assert(q.contains(2), "contains 2 check")
  assert(q.contains(3), "contains 3 check")
  assert(!q.contains(4), "contains 4 check")

  q.poll()

  assertEquals(q.head().value, 2)
  assertEquals(q.tail().value, 3)
  assertEquals(q.head().next.value, 3)
  assertEquals(q.tail().prev.value, 2)

  q.poll()

  assertEquals(q.head().value, 3)
  assertEquals(q.tail().value, 3)

  q.poll()

  assert(q.isEmpty())
}

const q1 = DQueue()
testQueueExhausted(q1)
testQueueExhausted(q1)
