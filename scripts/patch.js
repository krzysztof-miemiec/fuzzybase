const cpx = require('cpx');

console.log('Patching overridden modules...');
cpx.copySync('./patches/**', './node_modules');
