type t =
  | X
  | O;

let toggle = player =>
  switch (player) {
  | X => O
  | O => X
  };
