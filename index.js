const bindings = require('bindings')('flac-bindings')

function promisify(module) {
  for (let name in module) {
    if (
      typeof module[name] === 'function' &&
      name.substr(name.length - 4) !== 'sync'
    ) {
      const func = module[name]
      module[name] = function() {
        return new Promise((resolve, reject) => {
          const args = func(...Array.from(arguments), (err, data) => {
            if (err) {
              reject(err)
            } else {
              resolve(data)
            }
          })
        })
      }
    }
  }
}

promisify(bindings.format)
promisify(bindings.metadata_simple_iterator)
promisify(bindings.metadata_object)

module.exports = bindings
