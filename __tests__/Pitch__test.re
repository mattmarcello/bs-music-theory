open Jest;

describe("pitch", () => {
  test("sanity", () => {
    let key = Key.makeWithType(~type_=C, ());

    let pitch = Pitch.{key, octave: 1};

    Expect.(
      expect(
        {
          let pitch: Pitch.t = pitch->Pitch.addHalfstep(12);
          pitch.octave;
        },
      )
      |> toEqual(pitch.octave + 1)
    );
  });

  /* test("addHalfstep", () => { */

  /*   let pitch' = */
  /*     Pitch.make(~key=Key.makeWithType(~type_=C, ()), ~octave=1, ()) */
  /*     /1* ->Pitch.addHalfstep(1); *1/ */

  /*   let pitch'' = */
  /*     Pitch.make(~key=Key.makeWithType(~type_=C, ()), ~octave=1, ()) */
  /*     ->Pitch.addHalfstep(3); */

  /*   Js.log2("pitch one", pitch'.key  |> Key.normalizedIntValue  ) */
  /*   Js.log2("pitch two", pitch''.key |> Key.normalizedIntValue  ) */

  /*   Expect.(expect(pitch') |> not |> toBe(pitch'')) */

  /* }); */

  test("add halfstep", () => {
    let pitch =
      {key: Key.makeWithType(~type_=C, ()), octave: 1}
      ->Pitch.addHalfstep(1);

    let actual = pitch.key;

    let expected = Key.{type_: C, accidental: Accidental.sharp};

    Key.intEqual(actual, expected) ? pass : fail("");
  });

  test("subtract halfstep", () => {
    let pitch' =
      Pitch.{key: Key.makeWithType(~type_=C, ()), octave: 1}
      ->Pitch.subtractHalfstep(1);

    let pitch'' = Pitch.{key: Key.makeWithType(~type_=B, ()), octave: 0};

    Expect.(expect(pitch') |> toEqual(pitch''));
  });

  test("subtractPitch", () => {

    let c1 = Pitch.{key: Key.makeWithType(~type_=C, ()), octave: 1};

    let d1  = Pitch.{key: Key.makeWithType(~type_=D, ()), octave: 1};

    let actual = d1->Pitch.subtractPitch(c1);

    let expected = Interval.major2;

    Expect.(expect(actual) |> toEqual(expected));
  });
});




