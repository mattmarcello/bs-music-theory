module ChordThirdType:
  {
    type t = MusicTheory.Model.ChordThirdType.t = Major | Minor;
    let makeWithInterval: MusicTheory.Model.Interval.t => option(t);
    let interval: t => MusicTheory.Model.Interval.t;
    let notation: t => string;
    let description: t => string;
    let all: list(t);
  };
module ChordFifthType:
  {
    type t =
      MusicTheory.Model.ChordFifthType.t =
        Perfect
      | Diminished
      | Augmented;
    let makeWithInterval: MusicTheory.Model.Interval.t => option(t);
    let interval: t => MusicTheory.Model.Interval.t;
    let notation: t => string;
    let description: t => string;
    let all: list(t);
  };
module ChordSixthType:
  {
    type t = MusicTheory.Model.ChordSixthType.t = Sixth;
    let makeWithInterval: MusicTheory.Model.Interval.t => option(t);
    let interval: t => MusicTheory.Model.Interval.t;
    let notation: t => string;
    let description: t => string;
  };
module ChordSeventhType:
  {
    type t =
      MusicTheory.Model.ChordSeventhType.t =
        Major
      | Dominant
      | Diminished;
    let makeWithInterval: MusicTheory.Model.Interval.t => option(t);
    let interval: t => MusicTheory.Model.Interval.t;
    let notation: t => string;
    let description: t => string;
    let all: list(t);
  };
module ChordSuspendedType:
  {
    type t = MusicTheory.Model.ChordSuspendedType.t = Sus2 | Sus4;
    let makeWithInterval: MusicTheory.Model.Interval.t => option(t);
    let interval: t => MusicTheory.Model.Interval.t;
    let notation: t => string;
    let description: t => string;
    let all: list(t);
  };
module ChordExtensionType:
  {
    module ExtensionType:
      {
        type t =
          MusicTheory.Model.ExtensionType.t =
            Ninth
          | Eleventh
          | Thirteenth;
        let rawValue: t => int;
        let interval: t => MusicTheory.Model.Interval.t;
        let notation: t => string;
        let description: t => string;
        let all: list(t);
      };
    type t =
      MusicTheory.Model.ChordExtensionType.t = {
      type_: MusicTheory.Model.ExtensionType.t,
      accidental: MusicTheory.Model.Accidental.t,
      isAdded: bool,
    };
    let make:
      (~type_: MusicTheory.Model.ExtensionType.t,
      ~accidental: MusicTheory.Model.Accidental.t=?, unit) => t;
    let makeWithInterval: MusicTheory.Model.Interval.t  => option(t);
    let interval: t => MusicTheory.Model.Interval.t;
    let notation: t => string;
    let description: t => string;
    let all: Belt.List.t(t);
  };
type t =
  MusicTheory.Model.ChordType.t = {
  third: MusicTheory.Model.ChordThirdType.t,
  fifth: MusicTheory.Model.ChordFifthType.t,
  sixth: option(MusicTheory.Model.ChordSixthType.t),
  seventh: option(MusicTheory.Model.ChordSeventhType.t),
  suspended: option(MusicTheory.Model.ChordSuspendedType.t),
  extensions: option(list(MusicTheory.Model.ChordExtensionType.t)),
};
let makeWithIntervals: list(MusicTheory.Model.Interval.t) => option(t);
let make:
  (~third: ChordThirdType.t, ~fifth: ChordFifthType.t=?,
  ~sixth: ChordSixthType.t=?, ~seventh: ChordSeventhType.t=?,
  ~suspended: ChordSuspendedType.t=?,
  ~extensions: list(ChordExtensionType.t)=?, unit) => t;
let intervals: t => Belt.List.t(MusicTheory.Model.Interval.t);
let notation: t => string;
let description: t => string;
let all: list(t);
let equals: (option(t), option(t)) => bool;

module Infix : {
let (==): (option(t), option(t)) => bool;
}

