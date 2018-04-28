var flac = require('../lib')

arr = []
for (let i = 0; i < 10000; i++) {
  flac.metadata.new((err, it) => {
    if (err) console.error(err)
    arr.push(it)
  })
}

setTimeout(() => {
  arr = null
  gc()
}, 10000)

setTimeout(() => {}, 100000)
