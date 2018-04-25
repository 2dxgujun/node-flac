var bindings = require('bindings')('flac-bindings')

console.log(typeof bindings.metadata.SimpleIteratorStatusString[0])

for (let i in bindings.metadata.SimpleIteratorStatus) {
  console.log(typeof bindings.metadata.SimpleIteratorStatus[i])
  console.log(i)
}
//console.log(bindings.metadata.SimpleIteratorStatus)
