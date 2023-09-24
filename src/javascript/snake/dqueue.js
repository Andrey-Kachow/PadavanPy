const DQueue = () => {

  const Node = value => {
    return {
      value: value,
      next: null,
      prev: null
    }
  }

  let head = null
  let tail = null

  const isEmpty = () => {
    return head == null && tail == null
  }

  return {

    head: () => head,

    tail: () => tail,

    isEmpty: () => isEmpty(),

    add: value => {
      const newNode = Node(value)

      if (isEmpty()) {
        head = newNode
        tail = newNode
        return
      }
      tail.next = newNode
      newNode.prev = tail
      tail = newNode
    },

    poll: () => {
      if (isEmpty()) {
        throw "Empty poll"
      }
      if (head == tail) {
        tail = null
      }
      const res = head.value
      head = head.next
      return res
    },

    contains: value => {
      if (isEmpty()) {
        return false
      }
      let curr = tail
      while (curr != null) {
        if (curr.value == value) {
          return true
        }
        curr = curr.prev
      }
      return false
    }
  }
}
