
external register_types : unit -> Gobject.g_type array = "ml_gnome_canvas_register_types"

type canvas = [Gtk.layout|`canvas]
type item   = [`gtk|`canvasitem]
type group  = [item|`canvasgroup] 

(* GnomeCanvas *)

module Canvas = 
  struct
external new_canvas    : unit -> canvas Gobject.obj = "ml_gnome_canvas_new"
external new_canvas_aa : unit -> canvas Gobject.obj = "ml_gnome_canvas_new_aa"

external root : [> canvas] Gobject.obj -> group Gobject.obj = "ml_gnome_canvas_root"
external set_scroll_region : [> canvas] Gobject.obj -> x1:float -> y1:float -> x2:float -> y2:float -> unit = "ml_gnome_canvas_set_scroll_region"
external get_scroll_region : [> canvas] Gobject.obj -> float array = "ml_gnome_canvas_get_scroll_region"
external set_center_scroll_region : [> canvas] Gobject.obj -> bool -> unit = "ml_gnome_canvas_set_center_scroll_region"
external get_center_scroll_region : [> canvas] Gobject.obj -> bool = "ml_gnome_canvas_get_center_scroll_region"
external set_pixels_per_unit : [> canvas] Gobject.obj -> float -> unit = "ml_gnome_canvas_set_pixels_per_unit"
external scroll_to : [> canvas] Gobject.obj -> x:int -> y:int -> unit = "ml_gnome_canvas_scroll_to"
external get_scroll_offsets : [> canvas] Gobject.obj -> int * int = "ml_gnome_canvas_get_scroll_offsets"
external update_now : [> canvas] Gobject.obj -> unit = "ml_gnome_canvas_update_now"
external get_item_at : [> canvas] Gobject.obj -> x:float -> y:float -> item Gobject.obj = "ml_gnome_canvas_get_item_at"
external w2c_affine : [> canvas] Gobject.obj -> float array = "ml_gnome_canvas_w2c_affine"
external w2c : [> canvas] Gobject.obj -> wx:float -> wy:float -> int * int = "ml_gnome_canvas_w2c"
external w2c_d : [> canvas] Gobject.obj -> wx:float -> wy:float -> float * float = "ml_gnome_canvas_w2c_d"
external c2w : [> canvas] Gobject.obj -> cx:float -> cy:float -> float * float = "ml_gnome_canvas_c2w"
external window_to_world : [> canvas] Gobject.obj -> winx:float -> winy:float -> float * float = "ml_gnome_canvas_window_to_world"
external world_to_window : [> canvas] Gobject.obj -> wox:float -> woy:float -> float * float = "ml_gnome_canvas_world_to_window"

end

module Types : sig
  type 'a t constraint 'a = [> `gtk|`canvasitem]
  val group : [`gtk|`canvasitem|`canvasgroup] t
  val rect  : [`gtk|`canvasitem|`canvasshape|`canvasRE|`canvasrect] t
  val ellipse  : [`gtk|`canvasitem|`canvasshape|`canvasRE|`canvasellipse] t
end = 
  struct
  type 'a t = Gobject.g_type constraint 'a = [> `gtk|`canvasitem]
  let group = Gobject.Type.from_name "GnomeCanvasGroup"
  let rect  = Gobject.Type.from_name "GnomeCanvasRect"
  let ellipse = Gobject.Type.from_name "GnomeCanvasEllipse"
  end

(* GnomeCanvasItem *)
module Item =
  struct
external new_item : [> group] Gobject.obj -> 'a Types.t -> 'a Gobject.obj = "ml_gnome_canvas_item_new"
external parent : [> item] Gobject.obj -> group Gobject.obj = "ml_gnome_canvas_item_parent"
external set : [> item] Gobject.obj -> (string * Gobject.g_value) list -> unit = "ml_gnome_canvas_item_set"
external move : [> item] Gobject.obj -> x:float -> y:float -> unit = "ml_gnome_canvas_item_move"
external raise_item : [> item] Gobject.obj -> int -> unit = "ml_gnome_canvas_item_raise"
external lower : [> item] Gobject.obj -> int -> unit = "ml_gnome_canvas_item_lower"
external raise_to_top : [> item] Gobject.obj -> unit = "ml_gnome_canvas_item_raise_to_top"
external lower_to_bottom : [> item] Gobject.obj -> unit = "ml_gnome_canvas_item_lower_to_bottom"
external show : [> item] Gobject.obj -> unit = "ml_gnome_canvas_item_show"
external hide : [> item] Gobject.obj -> unit = "ml_gnome_canvas_item_hide"
external w2i : [> item] Gobject.obj -> x:float -> y:float -> float * float = "ml_gnome_canvas_item_w2i"
external i2w : [> item] Gobject.obj -> x:float -> y:float -> float * float = "ml_gnome_canvas_item_i2w"
external reparent : [> item] Gobject.obj -> group Gobject.obj -> unit = "ml_gnome_canvas_item_reparent"
external grab_focus : [> item] Gobject.obj -> unit = "ml_gnome_canvas_item_grab_focus"
external get_bounds : [> item] Gobject.obj -> float array = "ml_gnome_canvas_item_get_bounds"
module Signals = struct
  open GtkSignal
  let marshal f _ = function
    | `POINTER (Some p) :: _ -> f ((GdkEvent.unsafe_copy p) : Gdk.Tags.event_type Gdk.event)
    | _ -> invalid_arg "GnomeCanvas.Item.Signals.marshal"
  let event =
    { name = "event" ; classe = `canvasitem; marshaller = marshal; }
  end
end

(* GnomeCanvasGroup *)
module Group = 
  struct
external get_items : [> group] Gobject.obj -> item Gobject.obj list  = "ml_gnome_canvas_group_get_items"
end
