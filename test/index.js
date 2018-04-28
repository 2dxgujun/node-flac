var flac = require('../lib')
var Promise = require('bluebird')

function dumpRecursive(it, index = 0) {
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
            if (type === flac.format.MetadataType['PICTURE']) {
              console.log('FUCK')
            }
          })
        })
      })
    })
    .then(() => flac.metadata.next(it))
    .then(r => {
      if (r) return dumpRecursive(it, ++index)
    })
}

function dump(path) {
  return (
    flac.metadata
      .new()
      .then(it => {
        return flac.metadata.init(it, path, true, false).then(() => {
          return it
        })
      })
      .then(it => {
        return flac.metadata.is_writable(it).then(writable => {
          return it
        })
      })
      .then(dumpRecursive)
      .catch(err => {
        console.error(err)
      })
  )
}

function start() {
  const tasks = []
  for (let i = 0; i < 1; i++) {
    tasks.push('/Users/2dxgujun/Desktop/audio.flac')
  }
  return Promise.mapSeries(tasks, path => {
    return dump(path).then(gc)
  })
}

console.log('Start after 5 seconds')
gc()
setTimeout(() => {
  start().then(() => {
    console.log('Finished')
  })
}, 5000)

setTimeout(() => {}, 9999999)
