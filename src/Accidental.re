type t = Model.Accidental.t = | Natural | Flats(int) | Sharps(int);

let makeWithRawValue = i =>
  if (i == 0) {
    Natural;
  } else if (i > 0) {
    Sharps(i);
  } else {
    Flats(Js.Math.abs_int(i));
  };

let makeWithInteger = makeWithRawValue;

let makeWithString = str => {
  Js.String.split("", str)
  ->Belt.Array.reduce(0, (acc, curr) =>
      switch (curr) {
      | "#" => acc + 1

      /*
       TODO:
               Can't pattern match on unicode

            | {"♯"} => acc + 1 */
      | "b" => acc - 1

      /*

              | "♭" => acc - 1
       */
      | _ => acc
      }
    )
  |> makeWithInteger;
};

let rawValue =
  fun
  | Natural => 0
  | Flats(i) => - i
  | Sharps(i) => i;

let add = (a', a'') => makeWithInteger(a'->rawValue + a''->rawValue);

let subtract = (a', a'') => makeWithInteger(a'->rawValue - a''->rawValue);

let addInt = (a, i) => makeWithInteger(a->rawValue + i);

let subtractInt = (a, i) => makeWithInteger(a->rawValue - i);

let multiplyInt = (a, i) => makeWithInteger(a->rawValue * i);

let divideInt = (a, i) => makeWithInteger(a->rawValue / i);

let equals = (a', a'') => a'->rawValue == a''->rawValue;

let equalsStrict = (a', a'') =>
  switch (a', a'') {
  | (Natural, Natural) => true
  | (Sharps(a), Sharps(b)) when a == b => true
  | (Flats(a), Flats(b)) when a == b => true
  | _ => false
  };

let natural = Natural;

let flat = Flats(1);
let sharp = Sharps(1);

let doubleFlat = Flats(2);
let doubleSharp = Sharps(2);

let flats = i => Flats(i);
let sharps = i => Sharps(i);

let description =
  fun
  | Natural => ""
  | Flats(amount) => Js.String.repeat(amount, "b")
  | Sharps(amount) => {
      Js.String.repeat(amount, "#");
    };

let notation =
  fun
  | Natural => "♮"
  | type_ => description(type_);

