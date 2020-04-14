module Vdom = Virtual_dom.Vdom;
open Incr_dom;

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
