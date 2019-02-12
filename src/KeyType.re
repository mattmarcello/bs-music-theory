type t =
  | C
  | D
  | E
  | F
  | G
  | A
  | B;

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

let octaveDiff = (key, interval: Interval.t, octave) => {
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
        switch ((octave, currentKey^, next)) {
	 | (Octave.Higher, B, C) => diff^ + 1
	 | (Octave.Lower, C, B) => diff^ - 1
	 | _ => diff^
        }
      );

    currentKey := next

  };
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
