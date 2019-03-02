module ChordThirdType = {
  type t =
    | Major
    | Minor;

  let makeWithInterval: Interval.t => option(t) =
    interval => {
      Interval.(
        switch (interval) {
        | {quality: Major, degree: 3, semitones: 4} => Some(Major)
        | {quality: Minor, degree: 3, semitones: 3} => Some(Minor)
        | _ => None
        }
      );
    };

  let make =
    fun
    | `Interval(interval) => makeWithInterval(interval);

  let interval =
    fun
    | Major => Interval.major3
    | Minor => Interval.minor3;

  let notation =
    fun
    | Major => ""
    | Minor => "m";

  let description =
    fun
    | Major => "Major"
    | Minor => "Minor";

  let all = [Major, Minor];
};

module ChordFifthType = {
  type t =
    | Perfect
    | Diminished
    | Augmented;

  let makeWithInterval: Interval.t => option(t) =
    interval => {
      Interval.(
        switch (interval) {
        | {quality: Perfect, degree: 5, semitones: 7} => Some(Perfect)
        | {quality: Diminished, degree: 5, semitones: 6} => Some(Diminished)
        | {quality: Augmented, degree: 5, semitones: 8} => Some(Augmented)
        | _ => None
        }
      );
    };

  let make =
    fun
    | `Interval(interval) => makeWithInterval(interval);

  let interval =
    fun
    | Perfect => Interval.perfect5
    | Diminished => Interval.diminished5
    | Augmented => Interval.augmented5;

  let notation =
    fun
    | Perfect => ""
    | Augmented => "♯5" //TODO: confirm this is oka
    | Diminished => "♭5";

  let description =
    fun
    | Perfect => "Perfect"
    | Augmented => "Augmented" //TODO: confirm this is oka
    | Diminished => "Diminished";

  let all = [Perfect, Diminished, Augmented];
};

module ChordSixthType = {
  type t =
    | Sixth;

  let makeWithInterval: Interval.t => option(t) =
    interval => {
      Interval.(
        switch (interval) {
        | {quality: Major, degree: 6, semitones: 9} => Some(Sixth)
        | _ => None
        }
      );
    };

  let make =
    fun
    | `Interval(interval) => makeWithInterval(interval);

  let interval =
    fun
    | Sixth => Interval.major6;

  let notation =
    fun
    | Sixth => "6";

  let description =
    fun
    | Sixth => "Sixth";
};

module ChordSeventhType = {
  type t =
    | Major
    | Dominant
    | Diminished;

  let makeWithInterval: Interval.t => option(t) =
    interval => {
      Interval.(
        switch (interval) {
        | {quality: Major, degree: 7, semitones: 11} => Some(Major)
        | {quality: Minor, degree: 7, semitones: 10} => Some(Dominant)
        | {quality: Diminished, degree: 7, semitones: 9} => Some(Diminished)
        | _ => None
        }
      );
    };

  let make =
    fun
    | `Interval(interval) => makeWithInterval(interval);

  let interval =
    fun
    | Major => Interval.major7
    | Dominant => Interval.minor7
    | Diminished => Interval.diminished7;

  let notation =
    fun
    | Major => "maj7"
    | Dominant => "7" //TODO: confirm this is oka
    | Diminished => "dim7";

  let description =
    fun
    | Major => "Major 7th"
    | Dominant => "Dominant 7th" //TODO: confirm this is oka
    | Diminished => "Diminished 7th";

  let all = [Major, Dominant, Diminished];
};

module ChordSuspendedType = {
  type t =
    | Sus2
    | Sus4;

  let makeWithInterval: Interval.t => option(t) =
    interval => {
      Interval.(
        switch (interval) {
        | {quality: Major, degree: 2, semitones: 2} => Some(Sus2)
        | {quality: Perfect, degree: 4, semitones: 5} => Some(Sus4)
        | _ => None
        }
      );
    };

  let make =
    fun
    | `Interval(interval) => makeWithInterval(interval);

  let interval =
    fun
    | Sus2 => Interval.major2
    | Sus4 => Interval.perfect4;

  let notation =
    fun
    | Sus2 => "sus2"
    | Sus4 => "sus4";

  let description =
    fun
    | Sus2 => "Suspended 2nd"
    | Sus4 => "Suspended 4th";

  let all = [Sus2, Sus4];
};

module ChordExtensionType = {
  module ExtensionType = {
    type t =
      | Ninth
      | Eleventh
      | Thirteenth;

    let rawValue =
      fun
      | Ninth => 9
      | Eleventh => 11
      | Thirteenth => 13;

    let interval =
      fun
      | Ninth => Interval.major9
      | Eleventh => Interval.perfect11
      | Thirteenth => Interval.major13;

    let notation =
      fun
      | Ninth => "9"
      | Eleventh => "11"
      | Thirteenth => "13";

    let description =
      fun
      | Ninth => "9th"
      | Eleventh => "11th"
      | Thirteenth => "13th";

    let all = [Ninth, Eleventh, Thirteenth];
  };

  type t = {
    type_: ExtensionType.t,
    accidental: Accidental.t,
    isAdded: bool,
  };

  //TODO: consider renaming this
  let makeWithType =
      (~type_: ExtensionType.t, ~accidental=Accidental.Natural, ()) => {
    type_,
    accidental,
    isAdded: false,
  };

  // TODO: move and hide behind rei file addAcccidental defined originally defined in Chord.swift as an extension

  /* let addAccidental = (interval: t, accidental: Accidental.t) => { */
  /*   interval.semitones + accidental->Accidental.rawValue; */
  /* }; */

  let makeWithInterval = (~interval: Interval.t, ()) => {
    switch (interval.semitones) {
    /* ExtensionType.ninth.interval (14) + Accidental.natural (0) */
    | 14 =>
      Some({type_: Ninth, accidental: Accidental.Natural, isAdded: false})
    /* ExtensionType.ninth.interval (14) + Accidental.flat (-1) */
    | 13 => Some({type_: Ninth, accidental: Accidental.flat, isAdded: false})
    /* ExtensionType.ninth.interval (14) + Accidental.sharp (1) */
    | 15 => Some({type_: Ninth, accidental: Accidental.sharp, isAdded: false})
    /* ExtensionType.eleventh.interval (17) + Accidental.natural (0) */
    | 17 =>
      Some({type_: Eleventh, accidental: Accidental.Natural, isAdded: false})
    /* ExtensionType.eleventh.interval (17) + Accidental.flat (-1) */
    | 16 =>
      Some({type_: Eleventh, accidental: Accidental.flat, isAdded: false})
    /* ExtensionType.eleventh.interval (17) + Accidental.sharp (1) */
    | 18 =>
      Some({type_: Eleventh, accidental: Accidental.sharp, isAdded: false})
    /* ExtensionType.thirteenth.interval (21) + Accidental.natural (0) */
    | 21 =>
      Some({
        type_: Thirteenth,
        accidental: Accidental.Natural,
        isAdded: false,
      })
    /* ExtensionType.thirteenth.interval (21) + Accidental.flat (-1) */
    | 20 =>
      Some({type_: Thirteenth, accidental: Accidental.flat, isAdded: false})
    /* ExtensionType.thirteenth.interval (21) + Accidental.sharp (1) */
    | 22 =>
      Some({type_: Thirteenth, accidental: Accidental.sharp, isAdded: false})
    | _ => None
    };
  };

  let make = (~type_=?, ~accidental=Accidental.natural, ~interval=?, ()) => {
    switch (type_, interval) {
    | (Some(type_), _) => Some(makeWithType(~type_, ~accidental, ()))
    | (None, Some(interval)) => makeWithInterval(~interval, ())
    | _ =>
      Exception.Make("in Chord.make: must supply one of [ type_, interval ]")
      |> ignore;
      assert(false);
    };
  };

  let interval = ({type_, accidental}) => {
    switch (type_, accidental) {
    | (Ninth, Accidental.Natural) => Interval.major9
    | (Ninth, Flats(1)) => Interval.minor9
    | (Ninth, Sharps(1)) => Interval.augmented9
    | (Eleventh, Accidental.Natural) => Interval.perfect11
    | (Eleventh, Flats(1)) => Interval.perfect11
    | (Eleventh, Sharps(1)) => Interval.augmented11
    | (Thirteenth, Accidental.Natural) => Interval.major13
    | (Thirteenth, Flats(1)) => Interval.minor13
    | (Thirteenth, Sharps(1)) => Interval.augmented13
    | (Ninth, _) => Interval.major9
    | (Eleventh, _) => Interval.perfect11
    | (Thirteenth, _) => Interval.major13
    };
  };

  let notation = ({type_, accidental}) => {
    accidental->Accidental.notation ++ type_->ExtensionType.notation;
  };

  let description = ({type_, accidental, isAdded}) => {
    isAdded ?
      "Added " :
      ""
      ++ accidental->Accidental.description
      ++ " "
      ++ type_->ExtensionType.description;
  };

  let all =
    ExtensionType.all->Belt.List.reduce([], (acc, type_) =>
      acc->Belt.List.concat([
        make(~type_, ~accidental=Accidental.natural, ())->Belt.Option.getExn,
        make(~type_, ~accidental=Accidental.flat, ())->Belt.Option.getExn,
        make(~type_, ~accidental=Accidental.sharp, ())->Belt.Option.getExn,
      ])
    );
};

/* TODO: Math operators on Chord type */

  type t = {
    third: ChordThirdType.t,
    fifth: ChordFifthType.t,
    sixth: option(ChordSixthType.t),
    seventh: option(ChordSeventhType.t),
    suspended: option(ChordSuspendedType.t),
    extensions: option(list(ChordExtensionType.t)),
  };

  let makeWithIntervals: list(Interval.t) => option(t) =
    intervals => {
      let third = ref(None);
      let fifth = ref(None);
      let sixth = ref(None);
      let seventh = ref(None);
      let suspended = ref(None);
      let extensions = ref(None);

      intervals->Belt.List.forEach(interval => {
        let maybeThird = ChordThirdType.make(`Interval(interval));
        if (maybeThird->Belt.Option.isSome) {
          third := maybeThird;
        };

        let maybeFifth = ChordFifthType.make(`Interval(interval));
        if (maybeFifth->Belt.Option.isSome) {
          fifth := maybeFifth;
        };

        let maybeSixth = ChordSixthType.make(`Interval(interval));
        if (maybeSixth->Belt.Option.isSome) {
          sixth := maybeSixth;
        };

        let maybeSeventh = ChordSeventhType.make(`Interval(interval));
        if (maybeSeventh->Belt.Option.isSome) {
          seventh := maybeSeventh;
        };

        let maybeSuspended = ChordSuspendedType.make(`Interval(interval));
        if (maybeSuspended->Belt.Option.isSome) {
          suspended := maybeSuspended;
        };

        let maybeExtension = ChordExtensionType.make(~interval, ());

        if (maybeExtension->Belt.Option.isSome) {
          switch (extensions^) {
          | Some(extensions') =>
            extensions :=
              Some(
                Belt.List.concat(
                  extensions',
                  [maybeExtension->Belt.Option.getExn],
                ),
              )
          | None => extensions := Some([maybeExtension->Belt.Option.getExn])
          };
        };
      });

      // return None if third and fifth intervals are not supplied
      switch (third^, fifth^) {
      | (Some(third), Some(fifth)) =>
        Some({
          third,
          fifth,
          sixth: sixth^,
          seventh: seventh^,
          suspended: suspended^,
          extensions: extensions^,
        })

      | _ => None
      };
    };

  let make =
      (
        ~third: ChordThirdType.t,
        ~fifth: ChordFifthType.t=ChordFifthType.Perfect,
        ~sixth: option(ChordSixthType.t)=?,
        ~seventh: option(ChordSeventhType.t)=?,
        ~suspended: option(ChordSuspendedType.t)=?,
        ~extensions: option(list(ChordExtensionType.t))=?,
        (),
      ) => {
    {third, fifth, sixth, seventh, suspended, extensions};
  };

  let intervals = t => {
    [
      t.sixth->Belt.Option.isNone ?
        Some(t.third->ChordThirdType.interval) : None,
      t.suspended->Belt.Option.map(ChordSuspendedType.interval),
      Some(t.fifth->ChordFifthType.interval),
      t.sixth->Belt.Option.map(ChordSixthType.interval),
      t.seventh->Belt.Option.map(ChordSeventhType.interval),
    ]
    ->Belt.List.concat(
        {
          switch (t.extensions) {
          | Some((extensions: list(ChordExtensionType.t))) =>
            extensions
            ->Belt.List.sort((a, b) =>
                a.type_->ChordExtensionType.ExtensionType.rawValue
                - b.type_->ChordExtensionType.ExtensionType.rawValue
              )
            ->Belt.List.map(ChordExtensionType.interval)
            ->Belt.List.map(interval => Some(interval))
          | None => []
          };
        },
      )
    ->Belt.List.keepMap(Util.identity);
  };

  let notation = ({third, fifth, sixth, seventh, suspended, extensions}) => {
    let seventhNotation =
      ref(
        seventh->Belt.Option.mapWithDefault("", ChordSeventhType.notation),
      );

    let sixthNotation =
      ref(
        sixth->Belt.Option.mapWithDefault("", ChordSixthType.notation)
        ++ (seventh->Belt.Option.isSome ? "/" : ""),
      );

    let suspendedNotation =
      suspended->Belt.Option.mapWithDefault("", ChordSuspendedType.notation);

    let extensionNotation = {
      let ext =
        extensions->Belt.Option.mapWithDefault([], extensions =>
          extensions->Belt.List.sort((a, b) =>
            a.type_->ChordExtensionType.ExtensionType.rawValue
            - b.type_->ChordExtensionType.ExtensionType.rawValue
          )
        );

      let singleNotation = ref(ext->Belt.List.length > 0);

      for (i in 0 to ext->Belt.List.length - 1) {
        if (ext->Belt.List.getExn(i).accidental != Accidental.natural) {
          singleNotation := false;
        };
      };

      if (singleNotation^) {
        ext->Belt.List.reverse->Belt.List.headExn->ChordExtensionType.notation;
      } else {
        ext->Belt.List.map(ChordExtensionType.notation)->Belt.List.toArray
        |> Js.Array.joinWith("/");
      };
    };

    if (seventh->Belt.Option.isSome) {
      let seventh = Belt.Option.getExn(seventh);

      if (seventh == ChordSeventhType.Major
          && extensions->Belt.Option.getWithDefault([])->Belt.List.size > 0) {
        seventhNotation := "";
        sixthNotation :=
          (
            switch (sixth) {
            | Some(sixth) => sixth->ChordSixthType.notation
            | None => ""
            }
          );
      };

      if (fifth == ChordFifthType.Augmented
          || fifth == ChordFifthType.Diminished) {
        third->ChordThirdType.notation
        ++ sixthNotation^
        ++ seventhNotation^
        ++ fifth->ChordFifthType.notation
        ++ suspendedNotation
        ++ extensionNotation;
      } else {
        third->ChordThirdType.notation
        ++ fifth->ChordFifthType.notation
        ++ sixthNotation^
        ++ seventhNotation^
        ++ suspendedNotation
        ++ extensionNotation;
      };
    } else {
      third->ChordThirdType.notation
      ++ fifth->ChordFifthType.notation
      ++ sixthNotation^
      ++ seventhNotation^
      ++ suspendedNotation
      ++ extensionNotation;
    };
  };

  let description = ({third, fifth, sixth, seventh, suspended, extensions}) => {
    let seventhDescription =
      seventh->Belt.Option.map(ChordSeventhType.description);
    let sixthDescription = sixth->Belt.Option.map(ChordSixthType.description);
    let suspendedDescription =
      suspended->Belt.Option.map(ChordSuspendedType.description);

    let extensionDescriptions =
      extensions->Belt.Option.mapWithDefault([], l =>
        l
        ->Belt.List.sort((a, b) =>
            a.type_->ChordExtensionType.ExtensionType.rawValue
            - b.type_->ChordExtensionType.ExtensionType.rawValue
          )
        ->Belt.List.map(ChordExtensionType.notation)
        ->Belt.List.map(x => Some(x))
      );

    let desc =
      Belt.List.concat(
        [
          Some(third->ChordThirdType.description),
          Some(fifth->ChordFifthType.description),
          sixthDescription,
          seventhDescription,
          suspendedDescription,
        ],
        extensionDescriptions,
      )
      ->Belt.List.keepMap(Util.identity);

    desc->Belt.List.toArray |> Js.Array.joinWith("");
  };

  let all: list(t) = {
    let rec combinations =
            (~elements: list(ChordExtensionType.t), ~taking: int=1, ())
            : list(list(ChordExtensionType.t)) =>
      if (elements->Belt.List.length < 0) {
        [];
      } else if (elements->Belt.List.length <= 0 && taking <= 0) {
        [[]];
      } else if (taking == 1) {
        elements->Belt.List.map(el => [el]);
      } else {
        let comb = ref([[]]);

        for (index in 0 to elements->Belt.List.size - 1) {
          let element = elements->Belt.List.getExn(index);

          let reducedElements =
            elements->Belt.List.drop(index + 1)->Belt.Option.getExn;

          comb :=
            Belt.List.concat(
              comb^,
              combinations(~elements=reducedElements, ~taking=taking - 1, ())
              ->Belt.List.map(comb => Belt.List.concat([element], comb)),
            );
        };

        comb^;
      };

    let all = ref([]);

    let allThird = ChordThirdType.all;

    let allFifth = ChordFifthType.all;

    let allSixth = [Some(ChordSixthType.Sixth), None];

    let allSeventh =
      ChordSeventhType.all
      ->Belt.List.map(x => Some(x))
      ->Belt.List.concat([None]);

    let allSus =
      ChordSuspendedType.all
      ->Belt.List.map(x => Some(x))
      ->Belt.List.concat([None]);

    let allExt =
      combinations(~elements=ChordExtensionType.all, ~taking=1, ())
      ->Belt.List.concat(
          combinations(~elements=ChordExtensionType.all, ~taking=2, ()),
        )
      ->Belt.List.concat(
          combinations(~elements=ChordExtensionType.all, ~taking=3, ()),
        );

    allThird->Belt.List.forEach(third =>
      allFifth->Belt.List.forEach(fifth =>
        allSixth->Belt.List.forEach(sixth =>
          allSeventh->Belt.List.forEach(seventh =>
            allSus->Belt.List.forEach(suspended =>
              allExt->Belt.List.forEach(extensions =>
                all :=
                  Belt.List.concat(
                    all^,
                    [
                      make(
                        ~third,
                        ~fifth,
                        ~sixth?,
                        ~seventh?,
                        ~suspended?,
                        ~extensions,
                        (),
                      ),
                    ],
                  )
              )
            )
          )
        )
      )
    );

    all^;
  };

  let equals = (c': option(t), c'': option(t)): bool => {
    switch (c', c'') {
    | (Some(c'), Some(c'')) => c'->intervals == c''->intervals
    | (None, None) => true
    | _ => false
    };
  };

