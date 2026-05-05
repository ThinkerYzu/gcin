#ifdef GCIN_CORE_BUILD
  #include <stdarg.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include <string.h>
  #include <sys/types.h>
  #include <unistd.h>
  #include <time.h>
  void unix_exec(char *fmt, ...);
  typedef int           gboolean;
  typedef long long     gint64;
  typedef unsigned long KeySym;
  typedef void          GtkWidget;
  typedef void          Display;     /* phoa2d/tsa2d32 forward-declare send_gcin_message(Display*) */
  typedef char          unich_t;
  #define TRUE  1
  #define FALSE 0
  #define _L(x) x
  #define UNIX  1
  #define GTK_CHECK_VERSION(a,b,c) 0
  #define GTK_WIDGET_VISIBLE(w) (0)
  #define GDK_DISPLAY() ((Display*)0)
  #define g_malloc(n)    malloc(n)
  #define g_malloc0(n)   calloc(1, n)
  #define g_free(p)      free(p)
  #define g_strdup(s)    strdup(s)
  #define g_new(t,n)     ((t*)malloc(sizeof(t)*(n)))
  #define g_new0(t,n)    ((t*)calloc((n), sizeof(t)))
  #define g_realloc(p,n) realloc(p, n)
  /* g_strdup_printf: used in gcin-settings.cpp for UI color strings; result not needed in core build */
  static inline char *g_strdup_printf(const char *fmt, ...) {
    char buf[1024]; va_list ap; va_start(ap,fmt); vsnprintf(buf,sizeof(buf),fmt,ap); va_end(ap); return strdup(buf);
  }
  /* _(): gettext translation macro — identity in core build */
  #define _(x) (x)
  /* GLib types used by locale.cpp's Big5 conversion block */
  typedef void   GError;
  typedef size_t gsize;
  /* g_locale_from_utf8: Big5 conversion — not needed in core build; return strdup copy */
  static inline char *g_locale_from_utf8(const char *s, int l, gsize *rn, gsize *wn, GError **e) {
    (void)l; (void)rn; (void)wn; (void)e; return strdup(s);
  }
  /* g_markup_escape_text: used in gtab.cpp:htmlspecialchars; no escaping needed in core build */
  static inline char *g_markup_escape_text(const char *s, int len) { (void)len; return strdup(s); }
  /* XK_* key symbols used by feedkey_gtab / feedkey_pho */
  #define XK_space       0x0020
  #define XK_BackSpace   0xff08
  #define XK_Tab         0xff09
  #define XK_Return      0xff0d
  #define XK_Escape      0xff1b
  #define XK_Home        0xff50
  #define XK_Left        0xff51
  #define XK_Up          0xff52
  #define XK_Right       0xff53
  #define XK_Down        0xff54
  #define XK_Prior       0xff55
  #define XK_Next        0xff56
  #define XK_End         0xff57
  #define XK_Delete      0xffff
  #define XK_Shift_L     0xffe1
  #define XK_Shift_R     0xffe2
  #define XK_Control_L   0xffe3
  #define XK_Control_R   0xffe4
  #define XK_Caps_Lock   0xffe5
  #define XK_Alt_L       0xffe9
  #define XK_Alt_R       0xffea
  #define XK_KP_Enter    0xff8d
  #define XK_KP_Home     0xff95
  #define XK_KP_Left     0xff96
  #define XK_KP_Up       0xff97
  #define XK_KP_Right    0xff98
  #define XK_KP_Down     0xff99
  #define XK_KP_Prior    0xff9a
  #define XK_KP_Next     0xff9b
  #define XK_KP_End      0xff9c
  #define XK_KP_Delete   0xff9f
  #define XK_KP_Multiply 0xffaa
  #define XK_KP_Add      0xffab
  #define XK_KP_Subtract 0xffad
  #define XK_KP_Decimal  0xffae
  #define XK_KP_Divide   0xffaf
  #define XK_KP_Insert   0xff9e
  #define XK_KP_Begin    0xff9d
  #define XK_KP_0        0xffb0
  #define XK_KP_1        0xffb1
  #define XK_KP_2        0xffb2
  #define XK_KP_3        0xffb3
  #define XK_KP_4        0xffb4
  #define XK_KP_5        0xffb5
  #define XK_KP_6        0xffb6
  #define XK_KP_7        0xffb7
  #define XK_KP_8        0xffb8
  #define XK_KP_9        0xffb9
  #define XK_F1          0xffbe
  #define XK_F2          0xffbf
  #define XK_F3          0xffc0
  #define XK_F4          0xffc1
  #define XK_F5          0xffc2
  #define XK_F6          0xffc3
  #define XK_F7          0xffc4
  #define XK_F8          0xffc5
  #define XK_F9          0xffc6
  #define XK_F10         0xffc7
  #define XK_F11         0xffc8
  #define XK_F12         0xffc9
  #define ShiftMask      (1<<0)
  #define LockMask       (1<<1)
  #define ControlMask    (1<<2)
  #define Mod1Mask       (1<<3)
  #define Mod2Mask       (1<<4)
  #define Mod3Mask       (1<<5)
  #define Mod4Mask       (1<<6)
  #define Mod5Mask       (1<<7)
#else
  #include <stdarg.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <ctype.h>
  #include "os-dep.h"
  #include <gtk/gtk.h>
  #include <string.h>
  #if UNIX
  #include "IMdkit.h"
  #include "Xi18n.h"
  #endif
#endif
#if GCIN_i18n_message
#include <libintl.h>
#define _(STRING) gettext(STRING)
#else
#if UNIX
#define _(STRING) (STRING)
#else
#if _USRDLL
#define _(x) gmf.mf__utf16_8(x)
#else
#define _(x) __utf16_8(x)
#endif
#endif
#endif

#define N_(STRING) STRING

#include "gcin-gtk-compatible.h"

typedef enum {
  GCIN_STATE_DISABLED = 0,
  GCIN_STATE_ENG_FULL = 1,
  GCIN_STATE_CHINESE = 2
} GCIN_STATE_E;

/* change 3 to 4 if you want to use 4-byte UTF-8 characters, but you must
   regenerate *.gtab tsin
*/
#define CH_SZ (4)


#include "IC.h"

#if CLIENT_LIB
#define p_err __gcin_p_err
#define zmalloc __gcin_zmalloc
#endif

#include "util.h"

#define tmalloc(type,n)  (type*)malloc(sizeof(type) * (n))
void *zmalloc(int n);
void *memdup(void *p, int n);
#define tzmalloc(type,n)  (type*)zmalloc(sizeof(type) * (n))
#define trealloc(p,type,n)  (type*)realloc(p, sizeof(type) * (n+1))
#define tmemdup(p,type,n) (type*)memdup(p, sizeof(type) * n)
#ifndef GCIN_CORE_BUILD
#if UNIX
extern Display *dpy;
#endif
#endif

extern char *TableDir;

extern GtkWidget *gwin0;
#ifndef GCIN_CORE_BUILD
extern GdkWindow *gdkwin0;
extern Window xwin0;
extern Window root;
#if UNIX
void loadIC();
IC *FindIC(CARD16 icid);
#endif
#endif
extern ClientState *current_CS;

enum {
  InputStyleOverSpot = 1,
  InputStyleRoot = 2,
  InputStyleOnSpot = 4
};

typedef enum {
  Control_Space=0,
  Shift_Space=1,
  Alt_Space=2,
  Windows_Space=3,
} IM_TOGGLE_KEYS;

enum {
  TSIN_CHINESE_ENGLISH_TOGGLE_KEY_CapsLock=1,
  TSIN_CHINESE_ENGLISH_TOGGLE_KEY_Tab=2,
  TSIN_CHINESE_ENGLISH_TOGGLE_KEY_Shift=4,
  TSIN_CHINESE_ENGLISH_TOGGLE_KEY_ShiftL=8,
  TSIN_CHINESE_ENGLISH_TOGGLE_KEY_ShiftR=16,
};

typedef enum {
  TSIN_SPACE_OPT_SELECT_CHAR = 1,
  TSIN_SPACE_OPT_INPUT = 2,
} TSIN_SPACE_OPT;

enum {
  GCIN_EDIT_DISPLAY_OVER_THE_SPOT=1,
  GCIN_EDIT_DISPLAY_ON_THE_SPOT=2,
  GCIN_EDIT_DISPLAY_BOTH=4,
};

#define ROW_ROW_SPACING (2)


#define MAX_GCIN_STR (256)

#define PHO_KBM "phokbm"

extern int win_xl, win_yl;
extern int win_x, win_y;   // actual win x/y
extern int  current_in_win_x,  current_in_win_y;  // request x/y
extern int dpy_xl, dpy_yl;

extern int gcin_font_size;

void big5_utf8(char *s, char out[]);
void utf8_big5(char *s, char out[]);
#ifndef GCIN_CORE_BUILD
gint inmd_switch_popup_handler (GtkWidget *widget, GdkEvent *event);
#endif

#include "gcin-conf.h"

#define bchcpy(a,b) memcpy(a,b, CH_SZ)
#define bchcmp(a,b) memcmp(a,b, CH_SZ)

int utf8_sz(char *s);
int utf8cpy(char *t, char *s);
int u8cpy(char *t, char *s);
int utf8_tlen(char *s, int N);
void utf8_putchar(char *s);
void utf8_putcharn(char *s, int n);
gboolean utf8_eq(char *a, char *b);
gboolean utf8_str_eq(char *a, char *b, int len);
void utf8cpyN(char *t, char *s, int N);
int utf8_str_N(char *str);
void utf8cpyn(char *t, char *s, int n);
void utf8cpy_bytes(char *t, char *s, int n);
char *myfgets(char *buf, int bufN, FILE *fp);
void get_gcin_dir(char *tt);
#ifndef GCIN_CORE_BUILD
#if UNIX
Atom get_gcin_atom(Display *dpy);
#endif
#endif
void get_sys_table_file_name(char *name, char *fname);
char *half_char_to_full_char(KeySym xkey);
void send_text(char *text);
void send_utf8_ch(char *bchar);
void send_ascii(char key);
void bell();
void set_label_font_size(GtkWidget *label, int size);
#ifndef GCIN_CORE_BUILD
#if UNIX
void send_gcin_message(Display *dpy, char *s);
#else
void send_gcin_message(char *s);
#endif
#endif
void check_CS();
gint64 current_time();
void get_win_size(GtkWidget *win, int *width, int *height);
void change_win_fg_bg(GtkWidget *win, GtkWidget *label);
void set_no_focus(GtkWidget *win);
void change_win_bg(GtkWidget *win);
gboolean gcin_edit_display_ap_only();
gboolean gcin_display_on_the_spot_key();
void char_play(char *utf8);
void skip_utf8_sigature(FILE *fp);
#if WIN32
char *__utf16_8(wchar_t *s);
void win32_init_win(GtkWidget *win);
#endif

#define BITON(flag, bit) ((flag) & (bit))

typedef int usecount_t;

#define MAX_CIN_PHR (100*CH_SZ + 1)
