var bindings = require('bindings')('flac-bindings')

console.log(bindings.format.MetadataTypeString)
console.log(typeof bindings.format.FLAC__VERSION_STRING)
