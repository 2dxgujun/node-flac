var flac = require('../lib')

function main() {
  for (let i = 0; i < 1000; i++) {
    let it = flac.metadata.new_sync()
    flac.metadata.init_sync(
      it,
      '/Users/2dxgujun/Desktop/audio.flac',
      false,
      false
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
        flac.metadata_object.delete_sync(data)
        //console.log(data)
      }
    } while (flac.metadata.next_sync(it))

    it = null
    gc()
  }
}

gc()
setTimeout(() => {
  console.log('Started')
  main()
  console.log('Finished')
}, 5000)

setTimeout(() => {}, 100000)
