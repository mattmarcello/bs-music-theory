
  let indexOf = (l, elem) =>
    Belt.List.reduceWithIndex(l, None, (acc, curr, index) =>
      switch (acc) {
      | None when curr == elem => Some(index)
      | None => None
      | Some(_) => acc
      }
    );
