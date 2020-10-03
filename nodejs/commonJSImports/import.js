//get all exported data from exportExample.js
const exportExample = require("./exportExample.js");
console.log(exportExample);
//get only exported field 'bar' from exportExample.js
let { bar } = require("./exportExample.js");
console.log(bar);
//.js at the end is acceptable but not necessary
//require("./exportExample") == require("./exportExample.js")
bar = require("./exportExample").bar;
console.log(bar);
//get all exported data from file index.js inside folder/module aModule
const aModule = require("./aModule/index.js");
console.log(aModule);