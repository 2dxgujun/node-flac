var bindings = require('bindings')('flac-bindings')
var fs = require('fs')

function take(num) {
  if (num == 0) return
  fs.readFileSync('/Users/2dxgujun/Desktop/320.mp3')
  console.log(process.memoryUsage().rss / 1024 / 1024)
  setTimeout(() => {
    take(--num)
  }, 1000)
}

take(15)

function dump() {
  console.log(`dump: ${JSON.stringify(process.memoryUsage())}`)
  setTimeout(dump, 1000)
}

dump()

function _gc() {
  gc()
  setTimeout(_gc, 5000)
}

_gc()

setTimeout(() => {}, 100000)
