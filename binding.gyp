{
  "targets": [
    {
      "target_name": "flac-bindings",
      "sources": [
        "src/binding.cc",
        "src/format.cc",
        "src/metadata_level_1.cc",
        "src/metadata_object.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "<!@(pkg-config flac --cflags-only-I | sed s/-I//g)"
      ],
      "libraries": [
        "<!@(pkg-config flac --libs)"
      ]
    }
  ]
}
