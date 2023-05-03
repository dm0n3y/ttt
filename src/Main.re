module Vdom = Virtual_dom.Vdom;
open Incr_dom;

// Welcome to Reason!
//
// Reason is OCaml with modern syntax.
//
// Some differences (Reason vs OCaml):
// `f(x)`, `g(y, z)`  vs `f x`, `g y z`
// `list(int)`        vs `int list`
// `let _ = ...;`     vs `let _ = ... in`
// `switch (_) {...}` vs `match (_) with ...`
// `{...}`            vs `struct...end`, `sig...end`, etc

// Notes on new language features featured in this
// codebase that you haven't seen yet (not special
// to Reason, also available in OCaml)
// -  pipe operator (reverse function application)
//       x |> f(a, b)  ===  f(a, b, x)
//       (hint: think obj |> meth(a, b))
// -  labeled arguments
//       let circle = (~stroke: Color.t, ~radius: int) => {
//         ...
//       };
//       circle(~radius=4, ~stroke=Red);

module App = {
  module Model = Model;
  module Action = Update.Action;

  module State = {
    type t = unit;
  };

  let on_startup = (~schedule_action as _, _) => Async_kernel.Deferred.unit;

  let create =
      (
        model: Incr.t(Model.t),
        ~old_model as _: Incr.t(Model.t),
        ~inject: Update.Action.t => Vdom.Event.t,
      ) => {
    open Incr.Let_syntax;
    let%map model = model;
    Component.create(
      ~apply_action=
        (action, _, ~schedule_action as _) => Update.update(action, model),
      model,
      View.view(~inject, model),
    );
  };
};

Incr_dom.Start_app.start(
  (module App),
  ~bind_to_element_with_id="container",
  ~initial_model=App.Model.init,
);
