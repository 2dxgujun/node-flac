var flac = require('../lib')
var Promise = require('bluebird')

function dumpRecursive(it, index = 0) {
  return flac.metadata
    .get_block_type(it)
    .then(type => {
      //console.log(`METADATA BLOCK #${index}`)
      //console.log(`  type: ${type} (${flac.format.MetadataTypeString[type]})`)
      return flac.metadata.is_last(it).then(is_last => {
        //console.log(`  is last: ${is_last}`)
        return flac.metadata.get_block_length(it).then(length => {
          //console.log(`  length: ${length}`)
          return flac.metadata.get_block_offset(it).then(offset => {
            //console.log(`  offset: ${offset}`)
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
        //return flac.metadata.is_writable(it).then(writable => {
        //console.log(`is writable: ${writable}`)
        //return it
        //})
      })
      //.then(dumpRecursive)
      .catch(err => {
        console.error(err)
      })
  )
}

function start() {
  const tasks = []
  for (let i = 0; i < 10000; i++) {
    tasks.push('/Users/2dxgujun/Desktop/audio.flac')
  }
  return Promise.mapSeries(tasks, path => {
    return dump(path)
  })
}

console.log('Start after 5 seconds')
gc()
setTimeout(() => {
  start().then(() => {
    console.log('Finished, trigger GC after 10 seconds')
    setTimeout(() => {
      setInterval(gc, 1000)
      console.log('GC triggered')
    }, 10000)
  })
}, 5000)

setTimeout(() => {}, 9999999)
