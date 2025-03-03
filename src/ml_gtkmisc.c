/**************************************************************************/
/*                Lablgtk                                                 */
/*                                                                        */
/*    This program is free software; you can redistribute it              */
/*    and/or modify it under the terms of the GNU Library General         */
/*    Public License as published by the Free Software Foundation         */
/*    version 2, with the exception described in file COPYING which       */
/*    comes with the library.                                             */
/*                                                                        */
/*    This program is distributed in the hope that it will be useful,     */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of      */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the       */
/*    GNU Library General Public License for more details.                */
/*                                                                        */
/*    You should have received a copy of the GNU Library General          */
/*    Public License along with this program; if not, write to the        */
/*    Free Software Foundation, Inc., 59 Temple Place, Suite 330,         */
/*    Boston, MA 02111-1307  USA                                          */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

/* $Id$ */

#include <gtk/gtk.h>
#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/fail.h>

#include "wrappers.h"
#include "ml_glib.h"
#include "ml_gobject.h"
#include "ml_gdk.h"
#include "ml_pango.h"
#include "ml_gdkpixbuf.h"
#include "ml_gtk.h"
#include "gtk_tags.h"
#include "gdk_tags.h"

/* Init all */

CAMLprim value ml_gtkmisc_init(value unit)
{
    /* Since these are declared const, must force gcc to call them! */
    GType t =
        gtk_statusbar_get_type() +
        gtk_status_icon_get_type() +
        gtk_calendar_get_type() +
        gtk_drawing_area_get_type() +
        gtk_misc_get_type() +
        gtk_arrow_get_type() +
        gtk_image_get_type() +
        gtk_label_get_type() +
        gtk_hseparator_get_type() +
        gtk_vseparator_get_type() +
        gtk_font_selection_get_type() +
        gtk_color_selection_get_type();
    return Val_GType(t);
}

/* gtkstatusbar.h */

#define GtkStatusbar_val(val) check_cast(GTK_STATUSBAR,val)
ML_2 (gtk_statusbar_get_context_id, GtkStatusbar_val, String_val, Val_int)
ML_3 (gtk_statusbar_push, GtkStatusbar_val, Int_val, String_val, Val_int)
ML_2 (gtk_statusbar_pop, GtkStatusbar_val, Int_val, Unit)
ML_3 (gtk_statusbar_remove, GtkStatusbar_val, Int_val, Int_val, Unit)
/* not in 3
ML_1 (gtk_statusbar_get_has_resize_grip, GtkStatusbar_val, Val_bool)
ML_2 (gtk_statusbar_set_has_resize_grip, GtkStatusbar_val, Bool_val, Unit) */

/* gtkstatusicon.h */

#define GtkStatusIcon_val(val) check_cast(GTK_STATUS_ICON, val)
#define Val_GtkStatusIcon_new(val) Val_GObject_new(val)
ML_2 (gtk_status_icon_set_from_pixbuf, GtkStatusIcon_val, GdkPixbuf_val, Unit)
ML_2 (gtk_status_icon_set_from_file, GtkStatusIcon_val, String_val, Unit)
ML_2 (gtk_status_icon_set_from_stock, GtkStatusIcon_val, String_val, Unit)
ML_2 (gtk_status_icon_set_from_icon_name, GtkStatusIcon_val, String_val, Unit)
ML_1 (gtk_status_icon_get_pixbuf, GtkStatusIcon_val, Val_GdkPixbuf)
ML_1 (gtk_status_icon_get_stock, GtkStatusIcon_val, Val_string)
ML_1 (gtk_status_icon_get_icon_name, GtkStatusIcon_val, Val_string)
ML_1 (gtk_status_icon_get_size, GtkStatusIcon_val, Val_int)
ML_2 (gtk_status_icon_set_screen, GtkStatusIcon_val, GdkScreen_val, Unit)
ML_1 (gtk_status_icon_get_screen, GtkStatusIcon_val, Val_GdkScreen)
/* not in 3
ML_2 (gtk_status_icon_set_tooltip, GtkStatusIcon_val, String_val, Unit) */
ML_2 (gtk_status_icon_set_visible, GtkStatusIcon_val, Bool_val, Unit)
ML_1 (gtk_status_icon_get_visible, GtkStatusIcon_val, Val_bool)
/* not in 3
ML_2 (gtk_status_icon_set_blinking, GtkStatusIcon_val, Bool_val, Unit)
ML_1 (gtk_status_icon_get_blinking, GtkStatusIcon_val, Val_bool) */
ML_1 (gtk_status_icon_is_embedded, GtkStatusIcon_val, Val_bool)
/*
void                gtk_status_icon_position_menu       (GtkMenu *menu,
                                                         gint *x,
                                                         gint *y,
                                                         gboolean *push_in,
                                                         gpointer user_data);
gboolean            gtk_status_icon_get_geometry        (GtkStatusIcon *status_icon,
                                                         GdkScreen **screen,
                                                         GdkRectangle *area,
                                                         GtkOrientation *orientation);
guint32             gtk_status_icon_get_x11_window_id   (GtkStatusIcon *status_icon);
*/

/* gtkcalendar.h */

#define GtkCalendar_val(val) check_cast(GTK_CALENDAR,val)
ML_3 (gtk_calendar_select_month, GtkCalendar_val, Int_val, Int_val, Unit)
ML_2 (gtk_calendar_select_day, GtkCalendar_val, Int_val, Unit)
ML_2 (gtk_calendar_mark_day, GtkCalendar_val, Int_val, Unit)
ML_2 (gtk_calendar_unmark_day, GtkCalendar_val, Int_val, Unit)
ML_1 (gtk_calendar_clear_marks, GtkCalendar_val, Unit)
Make_Flags_val (Calendar_display_options_val)
ML_2 (gtk_calendar_set_display_options, GtkCalendar_val,
      Flags_Calendar_display_options_val, Unit)
CAMLprim value ml_gtk_calendar_get_date (value w)
{
    guint year, month, day;
    value ret;

    gtk_calendar_get_date (GtkCalendar_val(w), &year, &month, &day);
    ret = alloc_small (3, 0);
    Field(ret,0) = Val_int(year);
    Field(ret,1) = Val_int(month);
    Field(ret,2) = Val_int(day);
    return ret;
}
/* not in 3
ML_1 (gtk_calendar_freeze, GtkCalendar_val, Unit)
ML_1 (gtk_calendar_thaw, GtkCalendar_val, Unit)
Make_Extractor (gtk_calendar_get, GtkCalendar_val, num_marked_dates, Val_int) */
ML_2 (gtk_calendar_get_day_is_marked, GtkCalendar_val, Int_val, Val_bool)

/* gtkdrawingarea.h */

#define GtkDrawingArea_val(val) check_cast(GTK_DRAWING_AREA,val)
/* gtkmisc.h */

/* gtkarrow.h */

/* gtkimage.h */
#define GtkImage_val(val) check_cast(GTK_IMAGE,val)

#ifdef HASGTK28
ML_1(gtk_image_clear, GtkImage_val, Unit)
#else
Unsupported_28(gtk_image_clear)
#endif

/* gtklabel.h */

#define GtkLabel_val(val) check_cast(GTK_LABEL,val)
ML_2 (gtk_label_set_text, GtkLabel_val, String_val, Unit)
ML_1 (gtk_label_get_text, GtkLabel_val, Val_string)
ML_1 (gtk_label_get_layout, GtkLabel_val, Val_PangoLayout)
ML_3 (gtk_label_select_region, GtkLabel_val, Int_val, Int_val, Unit)
CAMLprim value ml_gtk_label_get_selection_bounds (value label)
{
  gint s, e;
  value r;
  if (gtk_label_get_selection_bounds (GtkLabel_val(label), &s, &e)) {
    r = alloc_small(2, 0);
    Field(r, 0) = Val_int(s);
    Field(r, 1) = Val_int(e);
    r = ml_some(r);
  }
  else
    r = Val_unit;
  return r;
}


/* gtk[hv]separator.h */
