var bindings = require('bindings')('flac-bindings')

var picturePath = '/Users/2dxgujun/Desktop/picture.jpeg'
var audioPath = '/Users/2dxgujun/Desktop/audio.flac'

var it = bindings.metadata.new((err, it) => {
  console.log(err)
  console.log(it)
})
//bindings.metadata.init(it, audioPath, false, false)
//
//do {
//  var blockType = bindings.metadata.get_block_type(it)
//  var blockTypeStr = bindings.format.MetadataTypeString[blockType]
//  console.log(`block type: ${blockTypeStr}`)
//} while (bindings.metadata.next(it))
