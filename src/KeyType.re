type t = MusicTheory.Model.KeyType.t = | C | D | E | F | G | A | B;

let makeWithString =
  fun
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
  | _ => assert(false);

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

let key = (key, ~at as distance: int) : t => {
  let index = Util.indexOf(all, key)->Belt.Option.getExn;

  let normalizedDistance = (index + distance) mod Belt.List.length(all);

  let keyIndex =
    normalizedDistance < 0 ?
      Belt.List.length(all) + normalizedDistance : normalizedDistance;

  Belt.List.getExn(all, keyIndex);
};

let distance = (key, ~from as keyType: t) => {
  let index' = all->Util.indexOf(key);
  let index'' = all->Util.indexOf(keyType);

  switch (index', index'') {
  | (Some(index'), Some(index'')) => index'' - index'
  | _ => 0
  };
};

let octaveDiff =
  (t, ~for_ as interval: Interval.t, ~isHigher) => {
    let diff = ref(0);
    let currentKey : ref(t) = ref(t);

    for (_ in 0 to interval.degree - 2) {
      let next =
	      isHigher ?
        (currentKey^ : t)->key(~at=1)
        : (currentKey^)->key(~at=-1);

      diff :=
        (
          switch (isHigher, currentKey^, next) {
          | (true, B, C) => diff^ + 1
          | (false, C, B) => diff^ - 1
          | _ => diff^
          }
        );

      currentKey := next;
    };

    diff^;
  };


let description  =
  fun
  | C => "C"
  | D => "D"
  | E => "E"
  | F => "F"
  | G => "G"
  | A => "A"
  | B => "B";

