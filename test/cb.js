var flac = require('../lib')

setTimeout(() => {
  let arr = []
  for (let i = 0; i < 100000; i++) {
    let it = flac.metadata.new_sync()
    //flac.metadata.init_sync(
    //  it,
    //  '/Users/2dxgujun/Desktop/audio.flac',
    //  false,
    //  false
    //)
    //flac.metadata.delete_sync(it)
    arr.push(it)
  }
  setTimeout(() => {
    arr.forEach(it => {
      flac.metadata.delete_sync(it)
    })
    arr = null
  }, 3000)
}, 5000)

setTimeout(() => {
  setInterval(gc, 1000)
}, 15000)

setTimeout(() => {}, 100000)
