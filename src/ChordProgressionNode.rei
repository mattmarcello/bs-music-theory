type t = Model.ChordProgressionNode.t = I | II | III | IV | V | VI | VII;
let next: t => list(t);
let all: list(t);
let description: t => string;
let rawValue: t => int;

