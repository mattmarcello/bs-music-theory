type t = Model.ChordProgression.t = { nodes: list(ChordProgressionNode.t), };
let make: list(ChordProgressionNode.t) => t;
let allNodes: t;
let i_v_vi_iv: t;
let vi_v_iv_v: t;
let i_vi_iv_v: t;
let i_iv_vi_v: t;
let i_v_iv_v: t;
let vi_ii_v_i: t;
let i_vi_ii_v: t;
let i_iv_ii_v: t;
let vi_iv_i_v: t;
let i_vi_iii_vii: t;
let vi_v_iv_iii: t;
let i_v_vi_iii_iv_i_iv_v: t;
let iv_i_v_iv: t;
let i_ii_vi_iv: t;
let i_iii_vi_iv: t;
let i_v_ii_iv: t;
let ii_iv_i_v: t;
let all: list(t);
let chords:
  (t, ~scale: Model.Scale.t, ~harmonicField: Model.HarmonicField.t,
  ~inversion: int=?, unit) => Belt.List.t(Model.Chord.t);
let description: t => string;
let equals: (t, t) => bool;
