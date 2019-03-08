type t = Model.Accidental.t = | Natural | Flats(int) | Sharps(int);

let makeWithRawValue: int => t;

let makeWithInteger: int => t;

let makeWithString: string => t;

let rawValue: t => int;

let add: (t, t) => t;

let subtract: (t, t) => t;

let addInt: (t, int) => t;

let subtractInt: (t, int) => t;

let multiplyInt: (t, int) => t;

let divideInt: (t, int) => t;

let equals: (t, t) => bool;

let equalsStrict: (t, t) => bool;

let natural: t;

let flat: t;

let sharp: t;

let doubleFlat: t;

let doubleSharp: t;

let flats: int => t;

let sharps: int => t;

/* rendering */

let notation: t => string;

let description: t => string;

