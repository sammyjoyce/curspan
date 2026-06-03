/*
 * cs_progress — one-shot progress bar. See cs_progress.h.
 */

#include "cs_progress.h"

#include <stdio.h>

#include "../ui/text_layout.h"
#include "cs_glyphs.h"

void cs_progress_render(const cs_progress_t *progress, cs_surface_t *s) {
  if (!progress || !s) {
    return;
  }
  cs_caps_t caps = cs_surface_caps(s);
  double fraction = progress->total > 0
                        ? (double)progress->current / (double)progress->total
                        : progress->value;
  if (fraction < 0.0) {
    fraction = 0.0;
  }
  if (fraction > 1.0) {
    fraction = 1.0;
  }

  cs_role_t bar_role =
      progress->bar_role ? progress->bar_role : CS_ROLE_SUCCESS;
  cs_role_t track_role =
      progress->track_role ? progress->track_role : CS_ROLE_MUTED;
  size_t width = progress->width ? progress->width : cs_surface_width(s);
  if (width == 0) {
    width = 80;
  }

  char percent[8] = {0};
  int percent_cols = 0;
  if (progress->show_percent) {
    snprintf(percent, sizeof(percent), " %3d%%", (int)(fraction * 100.0 + 0.5));
    percent_cols = app_text_width_utf8(percent);
  }

  int label_cols = 0;
  if (progress->label && progress->label[0]) {
    label_cols = app_text_width_utf8(progress->label) + 2;  // label + "  "
  }

  int bar_cols = (int)width - label_cols - percent_cols;
  if (bar_cols < 1) {
    bar_cols = 1;
  }
  int filled = (int)(fraction * bar_cols + 0.5);
  if (filled > bar_cols) {
    filled = bar_cols;
  }

  if (progress->label && progress->label[0]) {
    cs_surface_set_role(s, CS_ROLE_TEXT);
    cs_surface_write(s, progress->label);
    cs_surface_reset(s);
    cs_surface_write(s, "  ");
  }

  cs_surface_set_role(s, bar_role);
  cs_surface_repeat(s, cs_glyph_bar_full(caps.unicode), (size_t)filled);
  cs_surface_reset(s);
  cs_surface_set_role(s, track_role);
  cs_surface_repeat(s, cs_glyph_bar_empty(caps.unicode),
                    (size_t)(bar_cols - filled));
  cs_surface_reset(s);

  if (progress->show_percent) {
    cs_surface_set_role(s, CS_ROLE_MUTED);
    cs_surface_write(s, percent);
    cs_surface_reset(s);
  }
  cs_surface_newline(s);
}
