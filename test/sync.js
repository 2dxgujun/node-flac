var flac = require('../lib')

function main() {
  for (let i = 0; i < 1000; i++) {
    let it = flac.metadata.new_sync()
    flac.metadata.init_sync(
      it,
      '/Users/2dxgujun/Desktop/audio.flac',
      true,
      true
    )
    let index = 0
    do {
      //console.log(`METADATA BLOCK #${index++}`)
      //console.log(
      //  `  type: (${
      //    flac.format.MetadataTypeString[flac.metadata.get_block_type_sync(it)]
      //  })`
      //)
      //console.log(`  is last: ${flac.metadata.is_last_sync(it)}`)
      //console.log(`  length: ${flac.metadata.get_block_length_sync(it)}`)
      //console.log(`  offset: ${flac.metadata.get_block_offset_sync(it)}`)

      if (
        flac.metadata.get_block_type_sync(it) ===
        flac.format.MetadataType['PICTURE']
      ) {
        let data = flac.metadata.get_block_sync(it)
        let obj = flac.metadata_object.new_sync(
          flac.format.MetadataType['PICTURE']
        )
        flac.metadata_object
          .picture_set_mime_type(obj, 'audio/flac')
          .then(r => {
            return flac.metadata_object.picture_set_data(obj, Buffer.alloc(5))
          })
          .then(() => {
            return flac.metadata_object.picture_is_legal(obj)
          })
          .catch(err => {
            console.error(err)
          })
      }
    } while (flac.metadata.next_sync(it))

    it = null
    gc()
  }
}

main()

setTimeout(() => {}, 10000)
