#ifndef FLAC_BINDINGS__METADATA_H
#define FLAC_BINDINGS__METADATA_H

#define FLAC__MAX_METADATA_TYPE_CODE (126u)

#include <stdint.h>

typedef int8_t FLAC__int8;
typedef uint8_t FLAC__uint8;

typedef int16_t FLAC__int16;
typedef int32_t FLAC__int32;
typedef int64_t FLAC__int64;
typedef uint16_t FLAC__uint16;
typedef uint32_t FLAC__uint32;
typedef uint64_t FLAC__uint64;

typedef int FLAC__bool;
typedef FLAC__uint8 FLAC__byte;

struct FLAC__Metadata_SimpleIterator;

typedef struct FLAC__Metadata_SimpleIterator FLAC__Metadata_SimpleIterator;

typedef enum {
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_OK = 0,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_ILLEGAL_INPUT,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_ERROR_OPENING_FILE,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_NOT_A_FLAC_FILE,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_NOT_WRITABLE,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_BAD_METADATA,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_READ_ERROR,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_SEEK_ERROR,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_WRITE_ERROR,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_RENAME_ERROR,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_UNLINK_ERROR,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_MEMORY_ALLOCATION_ERROR,
  FLAC__METADATA_SIMPLE_ITERATOR_STATUS_INTERNAL_ERROR
} FLAC__Metadata_SimpleIteratorStatus;

typedef enum {
  FLAC__METADATA_TYPE_STREAMINFO = 0,
  FLAC__METADATA_TYPE_PADDING = 1,
  FLAC__METADATA_TYPE_APPLICATION = 2,
  FLAC__METADATA_TYPE_SEEKTABLE = 3,
  FLAC__METADATA_TYPE_VORBIS_COMMENT = 4,
  FLAC__METADATA_TYPE_CUESHEET = 5,
  FLAC__METADATA_TYPE_PICTURE = 6,
  FLAC__METADATA_TYPE_UNDEFINED = 7,
  FLAC__MAX_METADATA_TYPE = FLAC__MAX_METADATA_TYPE_CODE,
} FLAC__MetadataType;

typedef struct {
  unsigned min_blocksize, max_blocksize;
  unsigned min_framesize, max_framesize;
  unsigned sample_rate;
  unsigned channels;
  unsigned bits_per_sample;
  FLAC__uint64 total_samples;
  FLAC__byte md5sum[16];
} FLAC__StreamMetadata_StreamInfo;

typedef struct {
  int dummy;
} FLAC__StreamMetadata_Padding;

typedef struct {
  FLAC__byte id[4];
  FLAC__byte *data;
} FLAC__StreamMetadata_Application;

typedef struct {
  FLAC__uint64 sample_number;
  FLAC__uint64 stream_offset;
  unsigned frame_samples;
} FLAC__StreamMetadata_SeekPoint;

typedef struct {
  unsigned num_points;
  FLAC__StreamMetadata_SeekPoint *points;
} FLAC__StreamMetadata_SeekTable;

typedef struct {
  FLAC__uint32 length;
  FLAC__byte *entry;
} FLAC__StreamMetadata_VorbisComment_Entry;

typedef struct {
  FLAC__StreamMetadata_VorbisComment_Entry vendor_string;
  FLAC__uint32 num_comments;
  FLAC__StreamMetadata_VorbisComment_Entry *comments;
} FLAC__StreamMetadata_VorbisComment;

typedef struct {
  FLAC__uint64 offset;
  FLAC__byte number;
} FLAC__StreamMetadata_CueSheet_Index;

typedef struct {
  FLAC__uint64 offset;
  FLAC__byte number;
  char isrc[13];
  unsigned type:1;
  unsigned pre_emphasis:1;
  FLAC__byte num_indices;
  FLAC__StreamMetadata_CueSheet_Index *indices;
} FLAC__StreamMetadata_CueSheet_Track;

typedef struct {
  char media_catalog_number[129];
  FLAC__uint64 lead_in;
  FLAC__bool is_cd;
  unsigned num_tracks;
  FLAC__StreamMetadata_CueSheet_Track *tracks;
} FLAC__StreamMetadata_CueSheet;

typedef enum {
  FLAC__STREAM_METADATA_PICTURE_TYPE_OTHER = 0,
  FLAC__STREAM_METADATA_PICTURE_TYPE_FILE_ICON_STANDARD = 1,
  FLAC__STREAM_METADATA_PICTURE_TYPE_FILE_ICON = 2,
  FLAC__STREAM_METADATA_PICTURE_TYPE_FRONT_COVER = 3,
  FLAC__STREAM_METADATA_PICTURE_TYPE_BACK_COVER = 4,
  FLAC__STREAM_METADATA_PICTURE_TYPE_LEAFLET_PAGE = 5,
  FLAC__STREAM_METADATA_PICTURE_TYPE_MEDIA = 6,
  FLAC__STREAM_METADATA_PICTURE_TYPE_LEAD_ARTIST = 7,
  FLAC__STREAM_METADATA_PICTURE_TYPE_ARTIST = 8,
  FLAC__STREAM_METADATA_PICTURE_TYPE_CONDUCTOR = 9,
  FLAC__STREAM_METADATA_PICTURE_TYPE_BAND = 10,
  FLAC__STREAM_METADATA_PICTURE_TYPE_COMPOSER = 11,
  FLAC__STREAM_METADATA_PICTURE_TYPE_LYRICIST = 12,
  FLAC__STREAM_METADATA_PICTURE_TYPE_RECORDING_LOCATION = 13,
  FLAC__STREAM_METADATA_PICTURE_TYPE_DURING_RECORDING = 14,
  FLAC__STREAM_METADATA_PICTURE_TYPE_DURING_PERFORMANCE = 15,
  FLAC__STREAM_METADATA_PICTURE_TYPE_VIDEO_SCREEN_CAPTURE = 16,
  FLAC__STREAM_METADATA_PICTURE_TYPE_FISH = 17,
  FLAC__STREAM_METADATA_PICTURE_TYPE_ILLUSTRATION = 18,
  FLAC__STREAM_METADATA_PICTURE_TYPE_BAND_LOGOTYPE = 19,
  FLAC__STREAM_METADATA_PICTURE_TYPE_PUBLISHER_LOGOTYPE = 20,
  FLAC__STREAM_METADATA_PICTURE_TYPE_UNDEFINED
} FLAC__StreamMetadata_Picture_Type;

typedef struct {
  FLAC__StreamMetadata_Picture_Type type;
  char *mime_type;
  FLAC__byte *description;
  FLAC__uint32 width;
  FLAC__uint32 height;
  FLAC__uint32 depth;
  FLAC__uint32 colors;
  FLAC__uint32 data_length;
  FLAC__byte *data;
} FLAC__StreamMetadata_Picture;

typedef struct {
  FLAC__byte *data;
} FLAC__StreamMetadata_Unknown;

typedef struct {
  FLAC__MetadataType type;
  FLAC__bool is_last;
  unsigned length;
  union {
    FLAC__StreamMetadata_StreamInfo stream_info;
    FLAC__StreamMetadata_Padding padding;
    FLAC__StreamMetadata_Application application;
    FLAC__StreamMetadata_SeekTable seek_table;
    FLAC__StreamMetadata_VorbisComment vorbis_comment;
    FLAC__StreamMetadata_CueSheet cue_sheet;
    FLAC__StreamMetadata_Picture picture;
    FLAC__StreamMetadata_Unknown unknown;
  } data;
} FLAC__StreamMetadata;

#endif
