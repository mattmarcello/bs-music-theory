open Jest;

describe("pitch", () => {
  test("sanity", () => {
    let key = Key.makeWithType(~type_=C, ());

    let pitch = Pitch.make(~key, ~octave=1, ());

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

  test("key equality", () => {

    let pitch =
      Pitch.make(~key=Key.makeWithType(~type_=C, ()), ~octave=1, ())
      ->Pitch.addHalfstep(1);


    let actual = pitch.key;

    let expected = Key.{type_: C, accidental: Accidental.sharp};

    Js.log2("actual", actual);

    Js.log2("expected", expected);

    Js.log2("actual", actual->Key.normalizedIntValue);

    Js.log2("expected", expected->Key.normalizedIntValue);

    Key.intEqual(actual, expected) ? pass : fail("");
  });
});
