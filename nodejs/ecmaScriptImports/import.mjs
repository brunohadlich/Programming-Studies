//============importing from file============
//this kind of import selects the fields to be imported
import { foo } from './exportExample';
console.log(foo);
import { foo as fooNickname} from './exportExample';
console.log(fooNickname);
import { bar, baz } from './exportExample';
console.log(bar, baz);
//this kind of import does not select a field but a
//default value defined at file or module that is
//being imported
import exportExample from './exportExample';
console.log(exportExample);
//============importing from module============
import defaultFruit from './aModule';
console.log(defaultFruit);
import { banana, pineapple } from './aModule';
console.log(banana);
console.log(pineapple);
import * as fruits from './aModule';
console.log(fruits);
import { banana as favoriteFruit } from './aModule';
console.log(favoriteFruit);
import { apple, banana as againFavoriteFruit } from './aModule';
console.log(againFavoriteFruit);
import defaultFruit2, * as entireFruitsObject from './aModule';
console.log(defaultFruit2);
console.log(entireFruitsObject);