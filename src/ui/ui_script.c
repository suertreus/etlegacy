/*
 * Wolfenstein: Enemy Territory GPL Source Code
 * Copyright (C) 1999-2010 id Software LLC, a ZeniMax Media company.
 *
 * ET: Legacy
 * Copyright (C) 2012 Jan Simek <mail@etlegacy.com>
 *
 * This file is part of ET: Legacy - http://www.etlegacy.com
 *
 * ET: Legacy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ET: Legacy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ET: Legacy. If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, Wolfenstein: Enemy Territory GPL Source Code is also
 * subject to certain additional terms. You should have received a copy
 * of these additional terms immediately following the terms and conditions
 * of the GNU General Public License which accompanied the source code.
 * If not, please request a copy in writing from id Software at the address below.
 *
 * id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.
 */
/**
 * @file ui_script.c
 * @brief string allocation/managment
 */

#include "ui_shared.h"
#include "ui_local.h"

void Script_Show(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		Menu_ShowItemByName(item->parent, name, qtrue);
	}
}

void Script_SetColor(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	// expecting type of color to set and 4 args for the color
	if (String_Parse(args, &name))
	{
		vec4_t *out = NULL;

		if (Q_stricmp(name, "backcolor") == 0)
		{
			out                 = &item->window.backColor;
			item->window.flags |= WINDOW_BACKCOLORSET;
		}
		else if (Q_stricmp(name, "forecolor") == 0)
		{
			out                 = &item->window.foreColor;
			item->window.flags |= WINDOW_FORECOLORSET;
		}
		else if (Q_stricmp(name, "bordercolor") == 0)
		{
			out = &item->window.borderColor;
		}

		if (out)
		{
			float f = 0.0f;
			int   i;

			for (i = 0; i < 4; i++)
			{
				if (!Float_Parse(args, &f))
				{
					return;
				}

				(*out)[i] = f;
			}
		}
	}
}

void Script_SetBackground(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	// expecting name to set asset to
	if (String_Parse(args, &name))
	{
		item->window.background = DC->registerShaderNoMip(name);
	}
}

void Script_SetTeamColor(itemDef_t *item, qboolean *bAbort, char **args)
{
	if (DC->getTeamColor)
	{
		int    i;
		vec4_t color;

		DC->getTeamColor(&color);
		for (i = 0; i < 4; i++)
		{
			item->window.backColor[i] = color[i];
		}
	}
}

void Script_SetItemColor(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *itemname = NULL;
	const char *name     = NULL;

	// expecting type of color to set and 4 args for the color
	if (String_Parse(args, &itemname) && String_Parse(args, &name))
	{
		itemDef_t *item2;
		vec4_t    color;
		vec4_t    *out;
		int       j, i;
		int       count = Menu_ItemsMatchingGroup(item->parent, itemname);

		if (!Color_Parse(args, &color))
		{
			return;
		}

		for (j = 0; j < count; j++)
		{
			item2 = Menu_GetMatchingItemByNumber(item->parent, j, itemname);

			if (item2 != NULL)
			{
				out = NULL;
				if (Q_stricmp(name, "backcolor") == 0)
				{
					out = &item2->window.backColor;
				}
				else if (Q_stricmp(name, "forecolor") == 0)
				{
					out                  = &item2->window.foreColor;
					item2->window.flags |= WINDOW_FORECOLORSET;
				}
				else if (Q_stricmp(name, "bordercolor") == 0)
				{
					out = &item2->window.borderColor;
				}

				if (out)
				{
					for (i = 0; i < 4; i++)
					{
						(*out)[i] = color[i];
					}
				}
			}
		}
	}
}

void Script_SetMenuItemColor(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *menuname = NULL;
	const char *itemname = NULL;
	const char *name     = NULL;

	// expecting type of color to set and 4 args for the color
	if (String_Parse(args, &menuname) && String_Parse(args, &itemname) && String_Parse(args, &name))
	{
		menuDef_t *menu = Menus_FindByName(menuname);
		itemDef_t *item2;
		vec4_t    color;
		vec4_t    *out;
		int       j, i;
		int       count;

		if (!menu)
		{
			return;
		}

		count = Menu_ItemsMatchingGroup(menu, itemname);

		if (!Color_Parse(args, &color))
		{
			return;
		}

		for (j = 0; j < count; j++)
		{
			item2 = Menu_GetMatchingItemByNumber(menu, j, itemname);
			if (item2 != NULL)
			{
				out = NULL;
				if (Q_stricmp(name, "backcolor") == 0)
				{
					out = &item2->window.backColor;
				}
				else if (Q_stricmp(name, "forecolor") == 0)
				{
					out                  = &item2->window.foreColor;
					item2->window.flags |= WINDOW_FORECOLORSET;
				}
				else if (Q_stricmp(name, "bordercolor") == 0)
				{
					out = &item2->window.borderColor;
				}

				if (out)
				{
					for (i = 0; i < 4; i++)
					{
						(*out)[i] = color[i];
					}
				}
			}
		}
	}
}

void Script_Hide(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		Menu_ShowItemByName(item->parent, name, qfalse);
	}
}

void Script_FadeIn(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		Menu_FadeItemByName(item->parent, name, qfalse);
	}
}

void Script_FadeOut(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		Menu_FadeItemByName(item->parent, name, qtrue);
	}
}

void Script_Open(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		Menus_OpenByName(name);
	}
}

void Script_FadeInMenu(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		Menu_FadeMenuByName(name, bAbort, qfalse);
	}
}

void Script_FadeOutMenu(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		Menu_FadeMenuByName(name, bAbort, qtrue);
	}
}

void Script_ConditionalOpen(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *cvar  = NULL;
	const char *name1 = NULL;
	const char *name2 = NULL;
	int        testtype;  // 0: check val not 0
	// 1: check cvar not empty

	if (String_Parse(args, &cvar) && Int_Parse(args, &testtype) && String_Parse(args, &name1) && String_Parse(args, &name2))
	{
		float val;

		switch (testtype)
		{
		default:
		case 0:
			val = DC->getCVarValue(cvar);
			if (val == 0.f)
			{
				Menus_OpenByName(name2);
			}
			else
			{
				Menus_OpenByName(name1);
			}
			break;
		case 1:
		{
			char buff[1024];

			DC->getCVarString(cvar, buff, sizeof(buff));
			if (!buff[0])
			{
				Menus_OpenByName(name2);
			}
			else
			{
				Menus_OpenByName(name1);
			}
		}
		break;
		}
	}
}

void Script_ConditionalScript(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *cvar;
	const char *script1;
	const char *script2;
	const char *token;
	int        testtype;  // 0: check val not 0
	// 1: check cvar not empty
	int testval;

	if (String_Parse(args, &cvar) &&
	    Int_Parse(args, &testtype) &&
	    String_Parse(args, &token) && (token && *token == '(') &&
	    String_Parse(args, &script1) &&
	    String_Parse(args, &token) && (token && *token == ')') &&
	    String_Parse(args, &token) && (token && *token == '(') &&
	    String_Parse(args, &script2) &&
	    String_Parse(args, &token) && (token && *token == ')'))
	{
		float val;

		switch (testtype)
		{
		default:
		case 0:
			val = DC->getCVarValue(cvar);
			if (val == 0.f)
			{
				Item_RunScript(item, bAbort, script2);
			}
			else
			{
				Item_RunScript(item, bAbort, script1);
			}
			break;
		case 1:
		{
			char buff[1024];

			DC->getCVarString(cvar, buff, sizeof(buff));
			if (!buff[0])
			{
				Item_RunScript(item, bAbort, script2);
			}
			else
			{
				Item_RunScript(item, bAbort, script1);
			}
		}
		break;
		case 3:
			if (Int_Parse(args, &testval))
			{
				int testVal;

				val     = DC->getCVarValue(cvar);
				testVal = (int)val;
				if (testVal != testval)
				{
					Item_RunScript(item, bAbort, script2);
				}
				else
				{
					Item_RunScript(item, bAbort, script1);
				}
			}
			break;
		case 2:
			// special tests
			if (!Q_stricmp(cvar, "UIProfileIsActiveProfile"))
			{
				char ui_profileStr[256];
				char cl_profileStr[256];

				DC->getCVarString("ui_profile", ui_profileStr, sizeof(ui_profileStr));
				Q_CleanStr(ui_profileStr);
				Q_CleanDirName(ui_profileStr);

				DC->getCVarString("cl_profile", cl_profileStr, sizeof(cl_profileStr));

				if (!Q_stricmp(ui_profileStr, cl_profileStr))
				{
					Item_RunScript(item, bAbort, script1);
				}
				else
				{
					Item_RunScript(item, bAbort, script2);
				}
			}
			else if (!Q_stricmp(cvar, "UIProfileValidName"))
			{
				char ui_profileStr[256];
				char ui_profileCleanedStr[256];

				DC->getCVarString("ui_profile", ui_profileStr, sizeof(ui_profileStr));
				Q_strncpyz(ui_profileCleanedStr, ui_profileStr, sizeof(ui_profileCleanedStr));
				Q_CleanStr(ui_profileCleanedStr);
				Q_CleanDirName(ui_profileCleanedStr);

				if (*ui_profileStr && *ui_profileCleanedStr)
				{
					Item_RunScript(item, bAbort, script1);
				}
				else
				{
					Item_RunScript(item, bAbort, script2);
				}

			}
			else if (!Q_stricmp(cvar, "UIProfileAlreadyExists"))
			{
				char         ui_profileCleanedStr[256];
				qboolean     alreadyExists = qfalse;
				fileHandle_t f;

				DC->getCVarString("ui_profile", ui_profileCleanedStr, sizeof(ui_profileCleanedStr));
				Q_CleanStr(ui_profileCleanedStr);
				Q_CleanDirName(ui_profileCleanedStr);

				if (trap_FS_FOpenFile(va("profiles/%s/profile.dat", ui_profileCleanedStr), &f, FS_READ) >= 0)
				{
					alreadyExists = qtrue;
					trap_FS_FCloseFile(f);
				}

				if (alreadyExists)
				{
					Item_RunScript(item, bAbort, script1);
				}
				else
				{
					Item_RunScript(item, bAbort, script2);
				}
			}
			else if (!Q_stricmp(cvar, "UIProfileAlreadyExists_Rename"))
			{
				char         ui_profileCleanedStr[256];
				qboolean     alreadyExists = qfalse;
				fileHandle_t f;

				DC->getCVarString("ui_profile_renameto", ui_profileCleanedStr, sizeof(ui_profileCleanedStr));
				Q_CleanStr(ui_profileCleanedStr);
				Q_CleanDirName(ui_profileCleanedStr);

				if (trap_FS_FOpenFile(va("profiles/%s/profile.dat", ui_profileCleanedStr), &f, FS_READ) >= 0)
				{
					alreadyExists = qtrue;
					trap_FS_FCloseFile(f);
				}

				if (alreadyExists)
				{
					Item_RunScript(item, bAbort, script1);
				}
				else
				{
					Item_RunScript(item, bAbort, script2);
				}
			}
			else if (!Q_stricmp(cvar, "ReadyToCreateProfile"))
			{
				char         ui_profileStr[256], ui_profileCleanedStr[256];
				int          ui_rate;
				qboolean     alreadyExists = qfalse;
				fileHandle_t f;

				DC->getCVarString("ui_profile", ui_profileStr, sizeof(ui_profileStr));

				Q_strncpyz(ui_profileCleanedStr, ui_profileStr, sizeof(ui_profileCleanedStr));
				Q_CleanStr(ui_profileCleanedStr);
				Q_CleanDirName(ui_profileCleanedStr);

				if (trap_FS_FOpenFile(va("profiles/%s/profile.dat", ui_profileCleanedStr), &f, FS_READ) >= 0)
				{
					alreadyExists = qtrue;
					trap_FS_FCloseFile(f);
				}

				ui_rate = (int)DC->getCVarValue("ui_rate");

				if (!alreadyExists && *ui_profileStr && ui_rate > 0)
				{
					Item_RunScript(item, bAbort, script1);
				}
				else
				{
					Item_RunScript(item, bAbort, script2);
				}
			}
			else if (!Q_stricmp(cvar, "vidrestartIsRequired"))
			{
				int  ui_r_mode                           = DC->getCVarValue("ui_r_mode");
				int  ui_r_colorbits                      = DC->getCVarValue("ui_r_colorbits");
				int  ui_r_fullscreen                     = DC->getCVarValue("ui_r_fullscreen");
				int  ui_r_noborder                       = DC->getCVarValue("ui_r_noborder");
				int  ui_r_texturebits                    = DC->getCVarValue("ui_r_texturebits");
				int  ui_r_depthbits                      = DC->getCVarValue("ui_r_depthbits");
				int  ui_r_ext_compressed_textures        = DC->getCVarValue("ui_r_ext_compressed_textures");
				int  ui_r_allowextensions                = DC->getCVarValue("ui_r_allowextensions");
				int  ui_s_khz                            = DC->getCVarValue("ui_s_khz");
				int  ui_r_detailtextures                 = DC->getCVarValue("ui_r_detailtextures");
				int  ui_r_subdivisions                   = DC->getCVarValue("ui_r_subdivisions");
				int  ui_r_ext_texture_filter_anisotropic = DC->getCVarValue("ui_r_ext_texture_filter_anisotropic");
				int  ui_cg_shadows                       = DC->getCVarValue("ui_cg_shadows");
				char ui_r_texturemode[MAX_CVAR_VALUE_STRING];

				int  r_mode                           = DC->getCVarValue("r_mode");
				int  r_colorbits                      = DC->getCVarValue("r_colorbits");
				int  r_fullscreen                     = DC->getCVarValue("r_fullscreen");
				int  r_noborder                       = DC->getCVarValue("r_noborder");
				int  r_texturebits                    = DC->getCVarValue("r_texturebits");
				int  r_depthbits                      = DC->getCVarValue("r_depthbits");
				int  r_ext_compressed_textures        = DC->getCVarValue("r_ext_compressed_textures");
				int  r_allowextensions                = DC->getCVarValue("r_allowextensions");
				int  s_khz                            = DC->getCVarValue("s_khz");
				int  r_detailtextures                 = DC->getCVarValue("r_detailtextures");
				int  r_subdivisions                   = DC->getCVarValue("r_subdivisions");
				int  r_ext_texture_filter_anisotropic = DC->getCVarValue("r_ext_texture_filter_anisotropic");
				int  cg_shadows                       = DC->getCVarValue("cg_shadows");
				char r_texturemode[MAX_CVAR_VALUE_STRING];

				trap_Cvar_VariableStringBuffer("ui_r_texturemode", ui_r_texturemode, sizeof(ui_r_texturemode));
				trap_Cvar_VariableStringBuffer("r_texturemode", r_texturemode, sizeof(r_texturemode));

				if (ui_r_subdivisions != r_subdivisions ||
				    ui_r_mode != r_mode ||
				    ui_r_colorbits != r_colorbits ||
				    ui_r_fullscreen != r_fullscreen ||
				    ui_r_noborder != r_noborder ||
				    ui_r_texturebits != r_texturebits ||
				    ui_r_depthbits != r_depthbits ||
				    ui_r_ext_compressed_textures != r_ext_compressed_textures ||
				    ui_r_allowextensions != r_allowextensions ||
				    ui_s_khz != s_khz ||
				    ui_r_detailtextures != r_detailtextures ||
				    ui_r_ext_texture_filter_anisotropic != r_ext_texture_filter_anisotropic ||
				    ui_cg_shadows != cg_shadows ||
				    Q_stricmp(r_texturemode, ui_r_texturemode))
				{
					Item_RunScript(item, bAbort, script1);
				}
				else
				{
					Item_RunScript(item, bAbort, script2);
				}
				/*} else if( !Q_stricmpn( cvar, "voteflags", 9 ) ) {
				char info[MAX_INFO_STRING];
				int voteflags = atoi(cvar + 9);

				trap_Cvar_VariableStringBuffer( "cg_ui_voteFlags", info, sizeof(info) );

				if( (atoi(info) & item->voteFlag) != item->voteFlag ) {
				Item_RunScript( item, bAbort, script1 );
				} else {
				Item_RunScript( item, bAbort, script2 );
				}*/
#ifndef CGAMEDLL
			}
			else if (!Q_stricmpn(cvar, "serversort_", 11))
			{
				int sorttype = atoi(cvar + 11);

				if (sorttype != uiInfo.serverStatus.sortKey)
				{
					Item_RunScript(item, bAbort, script2);
				}
				else
				{
					Item_RunScript(item, bAbort, script1);
				}
			}
			else if (!Q_stricmp(cvar, "ValidReplaySelected"))
			{
				if (uiInfo.demoIndex >= 0 && uiInfo.demoIndex < uiInfo.demoCount)
				{
					Item_RunScript(item, bAbort, script1);
				}
				else
				{
					Item_RunScript(item, bAbort, script2);
				}
#endif // !CGAMEDLL
			}
			else if (!Q_stricmp(cvar, "ROldModeCheck"))
			{
				char r_oldModeStr[256];
				int  r_oldMode;
				int  r_mode = DC->getCVarValue("r_mode");

				DC->getCVarString("r_oldMode", r_oldModeStr, sizeof(r_oldModeStr));
				r_oldMode = atoi(r_oldModeStr);

				if (*r_oldModeStr && r_oldMode != r_mode)
				{
					Item_RunScript(item, bAbort, script1);
				}
				else
				{
					if (r_oldMode == r_mode)
					{
						trap_Cvar_Set("r_oldMode", "");   // clear it
					}

					Item_RunScript(item, bAbort, script2);
				}
			}

			break;
		}
	}
}

void Script_Close(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		Menus_CloseByName(name);
	}
}

void Script_CloseAll(itemDef_t *item, qboolean *bAbort, char **args)
{
	Menus_CloseAll();
}

void Script_CloseAllOtherMenus(itemDef_t *item, qboolean *bAbort, char **args)
{
	int i;

	for (i = 0; i < menuCount; i++)
	{
		if (&Menus[i] == item->parent)
		{
			continue;
		}

		Menu_RunCloseScript(&Menus[i]);
		Menus[i].window.flags &= ~(WINDOW_HASFOCUS | WINDOW_VISIBLE | WINDOW_MOUSEOVER);
	}
}

void Script_Transition(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		rectDef_t rectFrom, rectTo;
		float     amt  = 0.0f;
		int       time = 0;

		if (Rect_Parse(args, &rectFrom) && Rect_Parse(args, &rectTo) && Int_Parse(args, &time) && Float_Parse(args, &amt))
		{
			Menu_TransitionItemByName(item->parent, name, rectFrom, rectTo, time, amt);
		}
	}
}

void Script_Orbit(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		float cx   = 0.0f, cy = 0.0f, x = 0.0f, y = 0.0f;
		int   time = 0;

		if (Float_Parse(args, &x) && Float_Parse(args, &y) && Float_Parse(args, &cx) && Float_Parse(args, &cy) && Int_Parse(args, &time))
		{
			Menu_OrbitItemByName(item->parent, name, x, y, cx, cy, time);
		}
	}
}

void Script_SetFocus(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		itemDef_t *focusItem = Menu_FindItemByName(item->parent, name);

		if (focusItem && !(focusItem->window.flags & WINDOW_DECORATION) && !(focusItem->window.flags & WINDOW_HASFOCUS))
		{
			Menu_ClearFocus(item->parent);
			focusItem->window.flags |= WINDOW_HASFOCUS;
			if (focusItem->onFocus)
			{
				Item_RunScript(focusItem, NULL, focusItem->onFocus);
			}

			if (DC->Assets.itemFocusSound)
			{
				DC->startLocalSound(DC->Assets.itemFocusSound, CHAN_LOCAL_SOUND);
			}
		}
	}
}

void Script_ClearFocus(itemDef_t *item, qboolean *bAbort, char **args)
{
	Menu_ClearFocus(item->parent);
}

void Script_SetPlayerModel(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		DC->setCVar("team_model", name);
	}
}

void Script_SetPlayerHead(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		DC->setCVar("team_headmodel", name);
	}
}

// the parser misreads setCvar "bleh" ""
// you have to use clearCvar "bleh"
void Script_ClearCvar(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *cvar;

	if (String_Parse(args, &cvar))
	{
		DC->setCVar(cvar, "");
	}
}

void Script_SetCvar(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *cvar = NULL, *val = NULL;

	if (String_Parse(args, &cvar) && String_Parse(args, &val))
	{
		DC->setCVar(cvar, val);
	}
}

void Script_CopyCvar(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *cvar_src = NULL, *cvar_dst = NULL;

	if (String_Parse(args, &cvar_src) && String_Parse(args, &cvar_dst))
	{
		char buff[256];

		DC->getCVarString(cvar_src, buff, 256);
		DC->setCVar(cvar_dst, buff);
	}
}

void Script_Exec(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *val = NULL;

	if (String_Parse(args, &val))
	{
		DC->executeText(EXEC_APPEND, va("%s ; ", val));
	}
}

void Script_ExecNOW(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *val = NULL;

	if (String_Parse(args, &val))
	{
		DC->executeText(EXEC_NOW, va("%s ; ", val));
	}
}

void Script_Play(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *val = NULL;

	if (String_Parse(args, &val))
	{
		DC->startLocalSound(DC->registerSound(val, qfalse), CHAN_LOCAL_SOUND);          // all sounds are not 3d
	}
}

void Script_playLooped(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *val = NULL;

	if (String_Parse(args, &val))
	{
		DC->stopBackgroundTrack();
		DC->startBackgroundTrack(val, val, 0);
	}
}

void Script_AddListItem(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *itemname = NULL, *val = NULL, *name = NULL;

	if (String_Parse(args, &itemname) && String_Parse(args, &val) && String_Parse(args, &name))
	{
		itemDef_t *t = Menu_FindItemByName(item->parent, itemname);

		if (t && t->special)
		{
			DC->feederAddItem(t->special, name, atoi(val));
		}
	}
}

void Script_CheckAutoUpdate(itemDef_t *item, qboolean *bAbort, char **args)
{
	DC->checkAutoUpdate();
}

void Script_GetAutoUpdate(itemDef_t *item, qboolean *bAbort, char **args)
{
	DC->getAutoUpdate();
}

void Script_SetMenuFocus(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name;

	if (String_Parse(args, &name))
	{
		menuDef_t *focusMenu = Menus_FindByName(name);

		if (focusMenu && !(focusMenu->window.flags & WINDOW_HASFOCUS))
		{
			Menu_ClearFocus(item->parent);
			focusMenu->window.flags |= WINDOW_HASFOCUS;
		}
	}
}

qboolean Script_CheckProfile(char *profile_path)
{
	fileHandle_t f;
	char         f_data[32];
	int          f_pid;
	char         com_pid[256];
	int          pid;

	if (trap_FS_FOpenFile(profile_path, &f, FS_READ) < 0)
	{
		// no profile found, we're ok
		return qtrue;
	}

	trap_FS_Read(&f_data, sizeof(f_data) - 1, f);

	DC->getCVarString("com_pid", com_pid, sizeof(com_pid));
	pid = atoi(com_pid);

	f_pid = atoi(f_data);
	if (f_pid != pid)
	{
		// pid doesn't match
		trap_FS_FCloseFile(f);
		return qfalse;
	}

	// we're all ok
	trap_FS_FCloseFile(f);
	return qtrue;
}

qboolean Script_WriteProfile(char *profile_path)
{
	fileHandle_t f;
	char         com_pid[256];

	if (FileExists(profile_path))
	{
		trap_FS_Delete(profile_path);
	}

	if (trap_FS_FOpenFile(profile_path, &f, FS_WRITE) < 0)
	{
		Com_Printf("Script_WriteProfile: Can't write %s.\n", profile_path);
		return qfalse;
	}

	if (f < 0)
	{
		Com_Printf("Script_WriteProfile: Can't write %s.\n", profile_path);
		return qfalse;
	}

	DC->getCVarString("com_pid", com_pid, sizeof(com_pid));

	trap_FS_Write(com_pid, strlen(com_pid), f);

	trap_FS_FCloseFile(f);

	return qtrue;
}

void Script_ExecWolfConfig(itemDef_t *item, qboolean *bAbort, char **args)
{
	int useprofile = 1;

	if (Int_Parse(args, &useprofile))
	{
		char cl_profileStr[256];

		DC->getCVarString("cl_profile", cl_profileStr, sizeof(cl_profileStr));

		if (useprofile && cl_profileStr[0])
		{
			if (!Script_CheckProfile(va("profiles/%s/profile.pid", cl_profileStr)))
			{
#ifdef NDEBUG
				Com_Printf("^3WARNING: profile.pid found for profile '%s' - not executing %s\n", cl_profileStr, CONFIG_NAME);
#else
				DC->executeText(EXEC_NOW, va("exec profiles/%s/%s\n", cl_profileStr, CONFIG_NAME));
#endif // NDEBUG
			}
			else
			{
				DC->executeText(EXEC_NOW, va("exec profiles/%s/%s\n", cl_profileStr, CONFIG_NAME));

				if (!Script_WriteProfile(va("profiles/%s/profile.pid", cl_profileStr)))
				{
					Com_Printf("^3WARNING: couldn't write profiles/%s/profile.pid\n", cl_profileStr);
				}
			}
		}
	}
}

void Script_SetEditFocus(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *name = NULL;

	if (String_Parse(args, &name))
	{
		itemDef_t *editItem = Menu_FindItemByName(item->parent, name);

		if (editItem && TEXTFIELD(editItem->type))
		{
			editFieldDef_t *editPtr = (editFieldDef_t *)editItem->typeData;

			Menu_ClearFocus(item->parent);
			editItem->window.flags |= WINDOW_HASFOCUS;
			if (editItem->onFocus)
			{
				Item_RunScript(editItem, NULL, editItem->onFocus);
			}

			if (DC->Assets.itemFocusSound)
			{
				DC->startLocalSound(DC->Assets.itemFocusSound, CHAN_LOCAL_SOUND);
			}

			// reset scroll offset so we can see what we're editing
			if (editPtr)
			{
				editPtr->paintOffset = 0;
			}

			DC->setCVar(EDITFIELD_TEMP_CVAR, "");
			editItem->cursorPos = 0;
			g_editingField      = qtrue;
			g_editItem          = editItem;

			// the stupidest idea ever, let's just override the console, every ui element, user choice, etc
			// nuking this
			//DC->setOverstrikeMode(qtrue);
		}
	}
}

void Script_Abort(itemDef_t *item, qboolean *bAbort, char **args)
{
	*bAbort = qtrue;
}

// FIXME
void Script_GetClipboard(itemDef_t *item, qboolean *bAbort, char **args)
{
	char       clipbuff[1024];
	const char *temp = NULL;

#define CLIPFAIL *bAbort = qtrue; return;

	memset(clipbuff, 0, sizeof(clipbuff));
	DC->getClipboardData(clipbuff, sizeof(clipbuff));
	if (!strlen(clipbuff))
	{
		// abort if there is nothing in the clipboard
		CLIPFAIL;
	}

	if (!String_Parse(args, &temp))
	{
		CLIPFAIL;
	}

	if (Q_stricmp(temp, "cvar") == 0)
	{
		const char *token = NULL;

		if (!String_Parse(args, &token))
		{
			CLIPFAIL;
		}

		DC->setCVar(token, clipbuff);
	}
	else if (Q_stricmp(temp, "exec") == 0)
	{
		DC->executeText(EXEC_APPEND, va("%s ; ", clipbuff));
	}
	else if (Q_stricmp(temp, "eval") == 0)
	{
		const char *token = NULL;

		if (!String_Parse(args, &token))
		{
			CLIPFAIL;
		}

		// evaluate the string (temp)
		//TODO: handle
	}
}

// This is for toggling integer cvars using bitflags.
void Script_ToggleCvarBit(itemDef_t *item, qboolean *bAbort, char **args)
{
	const char *cvar = NULL, *val = NULL;

	if (String_Parse(args, &cvar) && String_Parse(args, &val))
	{
		int  bitvalue, value;
		char buff[256];

		DC->getCVarString(cvar, buff, 256);
		value    = atoi(buff);
		bitvalue = atoi(val);
		value   ^= bitvalue;
		DC->setCVar(cvar, va("%i", value));
	}
}

commandDef_t commandList[] =
{
	{ "fadein",             &Script_FadeIn             }, // group/name
	{ "fadeout",            &Script_FadeOut            }, // group/name
	{ "show",               &Script_Show               }, // group/name
	{ "hide",               &Script_Hide               }, // group/name
	{ "setcolor",           &Script_SetColor           }, // works on this
	{ "open",               &Script_Open               }, // menu
	{ "fadeinmenu",         &Script_FadeInMenu         }, // menu
	{ "fadeoutmenu",        &Script_FadeOutMenu        }, // menu

	{ "conditionalopen",    &Script_ConditionalOpen    }, // cvar menu menu
	// opens first menu if cvar is true[non-zero], second if false
	{ "conditionalscript",  &Script_ConditionalScript  }, // as conditonalopen, but then executes scripts

	{ "close",              &Script_Close              }, // menu
	{ "closeall",           &Script_CloseAll           },
	{ "closeallothermenus", &Script_CloseAllOtherMenus },

	{ "setbackground",      &Script_SetBackground      }, // works on this
	{ "setitemcolor",       &Script_SetItemColor       }, // group/name
	{ "setmenuitemcolor",   &Script_SetMenuItemColor   }, // group/name
	{ "setteamcolor",       &Script_SetTeamColor       }, // sets this background color to team color
	{ "setfocus",           &Script_SetFocus           }, // sets this background color to team color
	{ "clearfocus",         &Script_ClearFocus         },
	{ "setplayermodel",     &Script_SetPlayerModel     }, // sets this background color to team color
	{ "setplayerhead",      &Script_SetPlayerHead      }, // sets this background color to team color
	{ "transition",         &Script_Transition         }, // group/name
	{ "setcvar",            &Script_SetCvar            }, // group/name
	{ "clearcvar",          &Script_ClearCvar          },
	{ "copycvar",           &Script_CopyCvar           },
	{ "exec",               &Script_Exec               }, // group/name
	{ "execnow",            &Script_ExecNOW            }, // group/name
	{ "play",               &Script_Play               }, // group/name
	{ "playlooped",         &Script_playLooped         }, // group/name
	{ "orbit",              &Script_Orbit              }, // group/name
	{ "addlistitem",        &Script_AddListItem        }, // special command to add text items to list box
	{ "checkautoupdate",    &Script_CheckAutoUpdate    }, //
	{ "getautoupdate",      &Script_GetAutoUpdate      }, //
	{ "setmenufocus",       &Script_SetMenuFocus       }, // focus menu
	{ "execwolfconfig",     &Script_ExecWolfConfig     }, // executes etconfig.cfg
	{ "setEditFocus",       &Script_SetEditFocus       },
	{ "abort",              &Script_Abort              },
	{ "getclipboard",       &Script_GetClipboard       },
	{ "togglecvarbit",      &Script_ToggleCvarBit      },
};

int scriptCommandCount = sizeof(commandList) / sizeof(commandDef_t);

void Item_RunScript(itemDef_t *item, qboolean *bAbort, const char *s)
{
	char     script[4096], *p;
	qboolean bRan;
	qboolean b_localAbort = qfalse;

	Item_HandleSaveValue();

	memset(script, 0, sizeof(script));

	if (item && s && s[0])
	{
		int i;

		Q_strcat(script, 4096, s);
		p = script;
		while (1)
		{
			const char *command = NULL;

			// expect command then arguments, ; ends command, NULL ends script
			if (!String_Parse(&p, &command))
			{
				return;
			}

			if (command[0] == ';' && command[1] == '\0')
			{
				continue;
			}

			bRan = qfalse;
			for (i = 0; i < scriptCommandCount; i++)
			{
				if (Q_stricmp(command, commandList[i].name) == 0)
				{
					(commandList[i].handler(item, &b_localAbort, &p));
					bRan = qtrue;

					if (b_localAbort)
					{
						if (bAbort)
						{
							*bAbort = b_localAbort;
						}

						return;
					}

					break;
				}
			}
			// not in our auto list, pass to handler
			if (!bRan)
			{
				DC->runScript(&p);
			}
		}
	}
}
