var flac = require('../lib')

function dump(it, index = 0) {
  return flac.metadata
    .get_block_type(it)
    .then(type => {
      console.log(`METADATA BLOCK #${index}`)
      console.log(`  type: ${type} (${flac.format.MetadataTypeString[type]})`)
      return flac.metadata.is_last(it).then(is_last => {
        console.log(`  is last: ${is_last}`)
        return flac.metadata.get_block_length(it).then(length => {
          console.log(`  length: ${length}`)
          return flac.metadata.get_block_offset(it).then(offset => {
            console.log(`  offset: ${offset}`)
          })
        })
      })
    })
    .then(() => flac.metadata.next(it))
    .then(r => {
      if (r) return dump(it, ++index)
    })
}

function start() {
  return flac.metadata
    .new()
    .then(it =>
      flac.metadata.init(it, '/Users/2dxgujun/Desktop/audio.flac', true, false)
    )
    .then(it => {
      return flac.metadata.is_writable(it).then(writable => {
        console.log(`is writable: ${writable}`)
        return it
      })
    })
    .then(dump)
    .catch(err => {
      console.error(err)
    })
}

console.log('Start after 3 seconds')
setTimeout(() => {
  start().then(() => {
    console.log('Finished, trigger gc after 5 seconds')
    setTimeout(gc, 5000)
  })
}, 3000)

setTimeout(() => {}, Number.MAX_VALUE)
