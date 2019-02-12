type t =
  | Natural
  | Flats(int)
  | Sharps(int);

let flat = Flats(1);
let sharp = Sharps(1);

let doubleFlat = Flats(2);
let doubleSharp = Sharps(2);

let natural = Natural;

let flats = i => Flats(i);

let sharps = i => Sharps(i);

let rawValue =
  fun
  | Natural => 0
  | Flats(i) => - i
  | Sharps(i) => i;

let initializeWithInteger = i =>
  switch (i) {
  | 0 => Natural
  | i when i < 0 => Flats(- i)
  | _ => Sharps(i)
  };

let add = (a', a'') => initializeWithInteger(a'->rawValue + a''->rawValue);

let subtract = (a', a'') =>
  initializeWithInteger(a'->rawValue - a''->rawValue);

let addInt = (a, i) => initializeWithInteger(a->rawValue + i);

let subtractInt = (a, i) => initializeWithInteger(a->rawValue - i);

let multiplyInt = (a, i) => initializeWithInteger(a->rawValue * i);

let divideInt = (a, i) => initializeWithInteger(a->rawValue / i);

let toString = a => a->rawValue->string_of_int;
