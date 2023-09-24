function px(value) {
  return String(value) + "px"
}

function randint(min, max) {
  if (max < min) {
    throw `Incorrect range in randint: (${min}, ${max})`
  }
  else if (max == min) {
    return highest
  }
  return min + Math.floor((max - min + 1) * Math.random())
}
