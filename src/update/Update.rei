// Here is how we recieve user's input and update the model.
// You can define the fomate of the input by defining the type of Action.t
// but don't forget to synchronize the click_handler in the view.re
module Action: {
  [@deriving sexp]
  type t =
    | Mark(int);
};

let update: (Action.t, Model.t) => Model.t;
