const testAddon = require('./build/Release/testaddon.node');
function cb2(msg) {
    console.log('Callback 2');
    console.log(msg);
}

console.log('addon',testAddon);

const napi = new testAddon.NapiClass(5);
napi.setCb(cb2);
napi.runCb();
napi.runCb();
napi.runCb();
napi.runCb();

module.exports = testAddon;