var bindings = require('bindings')('flac-bindings')

console.log(bindings.metadata)

bindings.metadata.new((err, it) => {
  console.log(err)
  console.log(it)
})
