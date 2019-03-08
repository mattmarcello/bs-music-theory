type t = Model.ChordProgression.t = {nodes: list(ChordProgressionNode.t)};

let make = nodes => {nodes: nodes};

let allNodes = make(ChordProgressionNode.[I, II, III, IV, V, VI, VII]);

let i_v_vi_iv = make(ChordProgressionNode.[I, V, VI, IV]);

let vi_v_iv_v = make(ChordProgressionNode.[VI, V, IV, V]);

let i_vi_iv_v = make(ChordProgressionNode.[I, VI, IV, V]);

let i_iv_vi_v = make(ChordProgressionNode.[I, IV, VI, V]);

let i_v_iv_v = make(ChordProgressionNode.[I, V, IV, V]);

let vi_ii_v_i = make(ChordProgressionNode.[VI, II, V, I]);

let i_vi_ii_v = make(ChordProgressionNode.[I, VI, II, V]);

let i_iv_ii_v = make(ChordProgressionNode.[I, IV, II, V]);

let vi_iv_i_v = make(ChordProgressionNode.[VI, IV, I, V]);

let i_vi_iii_vii = make(ChordProgressionNode.[I, VI, III, VII]);

let vi_v_iv_iii = make(ChordProgressionNode.[VI, V, IV, III]);

let i_v_vi_iii_iv_i_iv_v =
  make(ChordProgressionNode.[I, V, VI, III, IV, I, IV, V]);

let iv_i_v_iv = make(ChordProgressionNode.[IV, I, V, IV]);

let i_ii_vi_iv = make(ChordProgressionNode.[I, II, VI, IV]);

let i_iii_vi_iv = make(ChordProgressionNode.[I, III, VI, IV]);

let i_v_ii_iv = make(ChordProgressionNode.[I, V, II, IV]);

let ii_iv_i_v = make(ChordProgressionNode.[II, IV, I, V]);

let all = [
  allNodes,
  i_v_vi_iv,
  vi_v_iv_v,
  i_vi_iv_v,
  i_iv_vi_v,
  i_v_iv_v,
  vi_ii_v_i,
  i_vi_ii_v,
  i_iv_ii_v,
  vi_iv_i_v,
  i_vi_iii_vii,
  vi_v_iv_iii,
  i_v_vi_iii_iv_i_iv_v,
  iv_i_v_iv,
  i_ii_vi_iv,
  i_iii_vi_iv,
  i_v_ii_iv,
  ii_iv_i_v,
];

let chords =
    (
      t,
      ~scale: Model.Scale.t,
      ~harmonicField: Model.HarmonicField.t,
      ~inversion=0,
      (),
    ) => {
  let indices = t.nodes->Belt.List.map(ChordProgressionNode.rawValue);
  let harmonics =
    scale->Scale.harmonicField(~for_=harmonicField, ~inversion, ());

  indices->Belt.List.reduce([], (acc, index) =>
    if (index < harmonics->Belt.List.size) {
      Belt.List.concat(acc, [harmonics->Belt.List.getExn(index)]);
    } else {
      acc;
    }
  );
};


let description = (t: t) =>
  if (t == allNodes) {
    "All";
  } else {
    t.nodes
    ->Belt.List.map(ChordProgressionNode.description)
    ->Belt.List.toArray
    |> Js.Array.joinWith("-");
  };


let equals = (t', t'') => {

	t'.nodes == t''.nodes
}
