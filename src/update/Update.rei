module Action: {
  [@deriving sexp]
  type t =
    | MarkSquare(Grid.index);
};

// Update of Model-View-Update architecture
let update: (Action.t, Model.t) => Model.t;
