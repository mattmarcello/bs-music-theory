type t =
  | C
  | D
  | E
  | F
  | G
  | A
  | B;

let make =
  fun
  | `StringLiteral(str) =>
    switch (str) {
    | "c"
    | "C" => C
    | "d"
    | "D" => D
    | "e"
    | "E" => E
    | "f"
    | "F" => F
    | "g"
    | "G" => G
    | "a"
    | "A" => A
    | "b"
    | "B" => B
    | _ => assert(false)
    };

/* let makeWithStringLiteral = str => { */
/*   let pattern = Js.Re.fromString("([A-Ga-g])([#♯♭b]*)"); */

/*   switch (str->Js.Re.exec(pattern)) { */
/*   | Some(match) when match->Js.Re.captures->Belt.Array.length == 3 => */
/*     let [_, key, accidental] = match->Js.Re.captures->Belt.List.fromArray; */

/*     D; */
/*   | _ => D */
/*   }; */
/* }; */

let make =
  fun
  | `StringLiteral(str) => C;

let rawValue =
  fun
  | C => 0
  | D => 2
  | E => 4
  | F => 5
  | G => 7
  | A => 9
  | B => 11;

let all = [C, D, E, F, G, A, B];

/**
  * TODO: refactor to at(~degree)
  */
let atDistance: (t, int) => t =
  (key, distance) => {
    let index = Util.indexOf(all, key)->Belt.Option.getExn;

    let normalizedDistance = (index + distance) mod Belt.List.length(all);

    let keyIndex =
      normalizedDistance < 0 ?
        Belt.List.length(all) + normalizedDistance : normalizedDistance;

    Belt.List.getExn(all, keyIndex);
  };

let distanceFrom = (key, target) => {
  let index' = all->Util.indexOf(key);
  let index'' = all->Util.indexOf(target);

  switch (index', index'') {
  | (Some(index'), Some(index'')) => index'' - index'
  | _ => 0
  };
};

//TODO: refactor this API
let octaveDiff: (t, Interval.t, Octave.t) => int =
  (key, interval: Interval.t, octave) => {
    let diff = ref(0);
    let currentKey = ref(key);
    for (_ in 0 to interval.degree - 1) {
      let next =
        switch (octave) {
        | Octave.Higher => key->atDistance(1)
        | Lower => key->atDistance(-1)
        };

      diff :=
        (
          switch (octave, currentKey^, next) {
          | (Octave.Higher, B, C) => diff^ + 1
          | (Octave.Lower, C, B) => diff^ - 1
          | _ => diff^
          }
        );

      currentKey := next;
    };

    diff^;
  };

let toString =
  fun
  | C => "C"
  | D => "D"
  | E => "E"
  | F => "F"
  | G => "G"
  | A => "A"
  | B => "B";
