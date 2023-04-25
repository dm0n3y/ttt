module Action = {
  [@deriving sexp]
  type t =
    | MarkSquare(Grid.index);
};

// Update of Model-View-Update architecture
let update = (_, _) => failwith("todo");