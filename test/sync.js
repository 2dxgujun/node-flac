var flac = require('../lib')

function main() {
  for (let i = 0; i < 1; i++) {
    let it = flac.metadata.new_sync()
    flac.metadata.init_sync(
      it,
      '/home/jun/Music/WalkmanGo/music/1.flac',
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
        flac.format.MetadataType['VORBIS_COMMENT']
      ) {
        let obj = flac.metadata.get_block_sync(it)
        console.log(obj)
        let num = flac.metadata_object.vorbiscomment_remove_entries_matching_sync(obj, 'ALBUM')
        console.log(num)
        flac.metadata.set_block_sync(it, obj, false)
      }
    } while (flac.metadata.next_sync(it))

    it = null
    gc()
  }
}

main()

setTimeout(() => {}, 10000)
