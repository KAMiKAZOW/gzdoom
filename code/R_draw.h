// Emacs style mode select	 -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// DESCRIPTION:
//		System specific interface stuff.
//
//-----------------------------------------------------------------------------


#ifndef __R_DRAW__
#define __R_DRAW__



extern byte**			ylookup;
extern int*				columnofs;

extern int				dc_pitch;		// [RH] Distance between rows

extern lighttable_t*	dc_colormap;
extern unsigned int*	dc_shademap;	// [RH] For high/true color modes
extern int				dc_x;
extern int				dc_yl;
extern int				dc_yh;
extern fixed_t			dc_iscale;
extern fixed_t			dc_texturemid;
extern int				dc_color;		// [RH] For flat colors (no texturing)

// first pixel in a column
extern byte*			dc_source;

// [RH] Temporary buffer for column drawing
extern byte				dc_temp[1200*4];
extern unsigned int		dc_tspans[4][256];
extern unsigned int		*dc_ctspan[4];
extern unsigned int		horizspans[4];

// [RH] Tutti-Frutti fix
unsigned int			dc_mask;


// [RH] Pointers to the different column and span drawers...

// The span blitting interface.
// Hook in assembler or system specific BLT here.
void (*R_DrawColumn)(void);

// The Spectre/Invisibility effect.
void (*R_DrawFuzzColumn)(void);

// [RH] Draw translucent column;
void (*R_DrawTranslucentColumn)(void);

// Draw with color translation tables,
//	for player sprite rendering,
//	Green/Red/Blue/Indigo shirts.
void (*R_DrawTranslatedColumn)(void);

// Span blitting for rows, floor/ceiling.
// No Sepctre effect needed.
void (*R_DrawSpan)(void);

// [RH] Span blit into an interleaved intermediate buffer
void (*R_DrawColumnHoriz)(void);
void R_DrawMaskedColumnHoriz (column_t *column);

// [RH] Initialize the above five pointers
void R_InitColumnDrawers (BOOL is8bit);

// [RH] Moves data from the temporary horizontal buffer to the screen.
void rt_copy1col_c (int hx, int sx, int yl, int yh);
void rt_copy2cols_c (int hx, int sx, int yl, int yh);
void rt_copy4cols_c (int sx, int yl, int yh);
void rt_map1col_c (int hx, int sx, int yl, int yh);
void rt_map2cols_c (int hx, int sx, int yl, int yh);
void rt_map4cols_c (int sx, int yl, int yh);
void rt_lucent1col (int hx, int sx, int yl, int yh);
void rt_lucent2cols (int hx, int sx, int yl, int yh);
void rt_lucent4cols (int sx, int yl, int yh);
void rt_tlate1col (int hx, int sx, int yl, int yh);
void rt_tlate2cols (int hx, int sx, int yl, int yh);
void rt_tlate4cols (int sx, int yl, int yh);
void rt_tlatelucent1col (int hx, int sx, int yl, int yh);
void rt_tlatelucent2cols (int hx, int sx, int yl, int yh);
void rt_tlatelucent4cols (int sx, int yl, int yh);
void rt_copy1col_asm (int hx, int sx, int yl, int yh);
void rt_copy2cols_asm (int hx, int sx, int yl, int yh);
void rt_copy4cols_asm (int sx, int yl, int yh);
void rt_map1col_asm (int hx, int sx, int yl, int yh);
void rt_map2cols_asm (int hx, int sx, int yl, int yh);
void rt_map4cols_asm (int sx, int yl, int yh);

#ifdef USEASM
#define rt_copy1col		rt_copy1col_asm
#define rt_copy2cols	rt_copy2cols_asm
#define rt_copy4cols	rt_copy4cols_asm
#define rt_map1col		rt_map1col_asm
#define rt_map2cols		rt_map2cols_asm
#define rt_map4cols		rt_map4cols_asm
#else
#define rt_copy1col		rt_copy1col_c
#define rt_copy2cols	rt_copy2cols_c
#define rt_copy4cols	rt_copy4cols_c
#define rt_map1col		rt_map1col_c
#define rt_map2cols		rt_map2cols_c
#define rt_map4cols		rt_map4cols_c
#endif

void rt_draw1col (int hx, int sx);
void rt_draw2cols (int hx, int sx);
void rt_draw4cols (int sx);

// [RH] Preps the temporary horizontal buffer.
void rt_initcols (void);


#ifndef USEASM
void	R_DrawColumnHorizP_C (void);
void	R_DrawColumnP_C (void);
void	R_DrawFuzzColumnP_C (void);
void	R_DrawTranslucentColumnP_C (void);
void	R_DrawTranslatedColumnP_C (void);
void	R_DrawSpanP (void);

void	R_DrawColumnD_C (void);
void	R_DrawFuzzColumnD_C (void);
void	R_DrawTranslucentColumnD_C (void);
void	R_DrawTranslatedColumnD_C (void);
void	R_DrawSpanD (void);

#else	/* USEASM */

void	R_DrawColumnP_Unrolled (void);
void	R_DrawSpanP_Unrolled (void);

void	R_DrawColumnHorizP_ASM (void);
void	R_DrawColumnP_ASM (void);
void	R_DrawFuzzColumnP_ASM (void);
void	R_DrawTranslucentColumnP_C (void);
void	R_DrawTranslatedColumnP_C (void);
void	R_DrawSpanP (void);

void	R_DrawColumnD_C (void);
void	R_DrawFuzzColumnD_C (void);
void	R_DrawTranslucentColumnD_C (void);
void	R_DrawTranslatedColumnD_C (void);
void	R_DrawSpanD (void);
#endif

void	R_DrawTlatedLucentColumnP_C (void);
#define R_DrawTlatedLucentColumn R_DrawTlatedLucentColumnP_C
void	R_StretchColumnP_C (void);
#define R_StretchColumn R_StretchColumnP_C

void	R_FillColumnP (void);
void	R_FillColumnHorizP (void);
void	R_FillSpan (void);

extern int				ds_colsize;		// [RH] Distance between columns
extern int				ds_colshift;

extern int				ds_y;
extern int				ds_x1;
extern int				ds_x2;

extern lighttable_t*	ds_colormap;

extern fixed_t			ds_xfrac;
extern fixed_t			ds_yfrac;
extern fixed_t			ds_xstep;
extern fixed_t			ds_ystep;

// start of a 64*64 tile image
extern byte*			ds_source;

extern int				ds_color;		// [RH] For flat color (no texturing)

extern byte*			translationtables;
extern byte*			dc_translation;

extern fixed_t dc_translevel;


/* [Petteri] R_DrawSpan8() optimized inner loop (does two pixels
   per cycle) */
void STACK_ARGS DrawSpan8Loop (fixed_t xfrac, fixed_t yfrac, int count, byte *dest);


// [RH] Double view pixels by detail mode
void R_DetailDouble (void);


void R_InitBuffer (int width, int height);


// Initialize color translation tables,
//	for player rendering etc.
void R_InitTranslationTables (void);

// [RH] Actually create a player's translation table.
void R_BuildPlayerTranslation (int player, int color);


// If the view size is not full screen, draws a border around it.
void R_DrawViewBorder (void);
void R_DrawTopBorder (void);
void R_DrawBorder (int x1, int y1, int x2, int y2);

// [RH] Added for muliresolution support
void R_InitFuzzTable (void);


#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
