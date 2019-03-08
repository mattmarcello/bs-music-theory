module ChordThirdType:
  {
    type t = Model.ChordThirdType.t = Major | Minor;
    let makeWithInterval: Model.Interval.t => option(t);
    let interval: t => Model.Interval.t;
    let notation: t => string;
    let description: t => string;
    let all: list(t);
  };
module ChordFifthType:
  {
    type t =
      Model.ChordFifthType.t =
        Perfect
      | Diminished
      | Augmented;
    let makeWithInterval: Model.Interval.t => option(t);
    let interval: t => Model.Interval.t;
    let notation: t => string;
    let description: t => string;
    let all: list(t);
  };
module ChordSixthType:
  {
    type t = Model.ChordSixthType.t = Sixth;
    let makeWithInterval: Model.Interval.t => option(t);
    let interval: t => Model.Interval.t;
    let notation: t => string;
    let description: t => string;
  };
module ChordSeventhType:
  {
    type t =
      Model.ChordSeventhType.t =
        Major
      | Dominant
      | Diminished;
    let makeWithInterval: Model.Interval.t => option(t);
    let interval: t => Model.Interval.t;
    let notation: t => string;
    let description: t => string;
    let all: list(t);
  };
module ChordSuspendedType:
  {
    type t = Model.ChordSuspendedType.t = Sus2 | Sus4;
    let makeWithInterval: Model.Interval.t => option(t);
    let interval: t => Model.Interval.t;
    let notation: t => string;
    let description: t => string;
    let all: list(t);
  };
module ChordExtensionType:
  {
    module ExtensionType:
      {
        type t =
          Model.ExtensionType.t =
            Ninth
          | Eleventh
          | Thirteenth;
        let rawValue: t => int;
        let interval: t => Model.Interval.t;
        let notation: t => string;
        let description: t => string;
        let all: list(t);
      };
    type t =
      Model.ChordExtensionType.t = {
      type_: Model.ExtensionType.t,
      accidental: Model.Accidental.t,
      isAdded: bool,
    };
    let make:
      (~type_: Model.ExtensionType.t,
      ~accidental: Model.Accidental.t=?, unit) => t;
    let makeWithInterval: Model.Interval.t  => option(t);
    let interval: t => Model.Interval.t;
    let notation: t => string;
    let description: t => string;
    let all: Belt.List.t(t);
  };
type t =
  Model.ChordType.t = {
  third: Model.ChordThirdType.t,
  fifth: Model.ChordFifthType.t,
  sixth: option(Model.ChordSixthType.t),
  seventh: option(Model.ChordSeventhType.t),
  suspended: option(Model.ChordSuspendedType.t),
  extensions: option(list(Model.ChordExtensionType.t)),
};
let makeWithIntervals: list(Model.Interval.t) => option(t);
let make:
  (~third: ChordThirdType.t, ~fifth: ChordFifthType.t=?,
  ~sixth: ChordSixthType.t=?, ~seventh: ChordSeventhType.t=?,
  ~suspended: ChordSuspendedType.t=?,
  ~extensions: list(ChordExtensionType.t)=?, unit) => t;


let intervals: t => Belt.List.t(Model.Interval.t);

let notation: t => string;
let description: t => string;
let all: list(t);
let equals: (option(t), option(t)) => bool;

