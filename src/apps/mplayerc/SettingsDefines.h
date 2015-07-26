/*
 * (C) 2006-2015 see Authors.txt
 *
 * This file is part of MPC-BE.
 *
 * MPC-BE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-BE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#define DEFAULT_CACHE_LENGTH	64		// in Kb

#define MINQUEUEPACKETS			50
#define MAXQUEUEPACKETS			500
#define MINQUEUESIZE			256		// in Kb
#define MAXQUEUESIZE			128		// in Mb

#define IDS_R_SETTINGS						_T("Settings")
#define IDS_R_FILTERS						_T("Filters")
#define IDS_R_INTERNAL_FILTERS				_T("InternalFilters")
#define IDS_R_FAVFILES						_T("Favorites\\Files")
#define IDS_R_FAVDVDS						_T("Favorites\\DVDs")
#define IDS_R_FAVDEVICES					_T("Favorites\\Devices")
#define IDS_R_COMMANDS						_T("Commands2")
#define IDS_R_LOGINS						_T("Logins")
#define IDS_R_FAVORITES						_T("Favorites")
#define IDS_R_SHADERS						_T("Shaders")

#define IDS_RS_FAV_REMEMBERPOS				_T("RememberPosition")
#define IDS_RS_FAV_RELATIVEDRIVE			_T("RelativeDrive")
#define IDS_RS_DVDPOS						_T("Remember DVD Pos")
#define IDS_RS_DVD_START_MAIN_TITLE			_T("Start Main Title DVD")
#define IDS_RS_DVD_MADVR_CHANGE				_T("Change madVR to Another renderer")
#define IDS_RS_FILEPOS						_T("Remember File Pos")
#define IDS_RS_EVR_BUFFERS					_T("EVRBuffers")
#define IDS_RS_SHOWOSD						_T("ShowOSD")
#define IDS_RS_LANGUAGE						_T("Language")
#define IDS_RS_GLOBALMEDIA					_T("UseGlobalMedia")
#define IDS_RS_DXVAFILTERS					_T("DXVAFilters")
#define IDS_RS_FFMPEGFILTERS				_T("FFmpegFilters")
#define IDS_RS_TITLEBARTEXTSTYLE			_T("TitleBarTextStyle")
#define IDS_RS_USEWMASFREADER				_T("UseWMASFReader")
#define IDS_RS_CONTROLSTATE					_T("ControlState")
#define IDS_RS_VOLUME						_T("Volume")
#define IDS_RS_MUTE							_T("Mute")
#define IDS_RS_BALANCE						_T("Balance")
#define IDS_RS_LOOP							_T("Loop")
#define IDS_RS_SNAPTODESKTOPEDGES			_T("SnapToDesktopEdges")
#define IDS_RS_ENABLESUBTITLES				_T("EnableSubtitles")
#define IDS_RS_FORCEDSUBTITLES				_T("ForcedSubtitles")
#define IDS_RS_PRIORITIZEEXTERNALSUBTITLES	_T("PrioritizeExternalSubtitles")
#define IDS_RS_DISABLEINTERNALSUBTITLES		_T("DisableInternalSubtitles")
#define IDS_RS_AUTORELOADEXTSUBTITLES		_T("AutoReloadExtSubtitles")
#define IDS_RS_USE_SUBRESYNC				_T("UseSubresync")
#define IDS_RS_SUBTITLEPATHS				_T("SubtitlePaths")
#define IDS_RS_USEDEFAULTSUBTITLESSTYLE		_T("UseDefaultsubtitlesStyle")
#define IDS_RS_MPEGINTERLACED				_T("MPEGInterlaced")
#define IDS_RS_THUMBWIDTH					_T("ThumbWidth")

#define IDS_RS_SUBSAVEEXTERNALSTYLEFILE		_T("SubSaveExternalStyleFile")

#define IDS_RS_AUDIOMIXER					_T("AudioMixer")
#define IDS_RS_AUDIOMIXERLAYOUT				_T("AudioMixerLayout")
#define IDS_RS_AUDIOGAIN					_T("AudioGain")
#define IDS_RS_AUDIOAUTOVOLUMECONTROL		_T("AudioAutoVolumeControl")
#define IDS_RS_AUDIONORMBOOST				_T("AudioNormBoost")
#define IDS_RS_AUDIONORMLEVEL				_T("AudioNormLevel")
#define IDS_RS_AUDIONORMREALEASETIME		_T("AudioNormRealeaseTime")


#define IDS_RS_D3DFULLSCREEN				_T("D3DFullScreen")
#define IDS_RS_MONITOR_AUTOREFRESHRATE		_T("MonitorAutoRefreshRate")
#define IDS_RS_COLOR_BRIGHTNESS				_T("VideoBrightness")
#define IDS_RS_COLOR_CONTRAST				_T("VideoContrast")
#define IDS_RS_COLOR_HUE					_T("VideoHue")
#define IDS_RS_COLOR_SATURATION				_T("VideoSaturation")
#define IDS_RS_SHADERLIST					_T("Shaders List")
#define IDS_RS_TITLEBARTEXTTITLE			_T("TitleBarTextTitle")
#define IDS_RS_LOOPNUM						_T("LoopNum")
#define IDS_RS_REWIND						_T("Rewind")
#define IDS_RS_ZOOM							_T("Zoom")
#define IDS_RS_AUTOFITFACTOR				_T("AutoFitFactor")
#define IDS_RS_VOLUME_STEP					_T("VolumeStep")
#define IDS_RS_SPEED_STEP					_T("SpeedStep")
#define IDS_RS_MULTIINST					_T("MultipleInstances")
#define IDS_RS_ALWAYSONTOP					_T("AlwaysOnTop")
#define IDS_RS_AUTOZOOM						_T("AutoZoom")
#define IDS_RS_FULLSCREENCTRLS				_T("FullScreenCtrls")
#define IDS_RS_FULLSCREENCTRLSTIMEOUT		_T("FullScreenCtrlsTimeOut")
#define IDS_RS_VMRFLIP						_T("VMRFlip")
#define IDS_RS_DVDPATH						_T("DVDPath")
#define IDS_RS_USEDVDPATH					_T("UseDVDPath")
#define IDS_RS_MENULANG						_T("MenuLang")
#define IDS_RS_AUDIOLANG					_T("AudioLang")
#define IDS_RS_SUBTITLESLANG				_T("SubtitlesLang")
#define IDS_RS_SPLOGFONT					_T("SPDefaultStyle")
#define IDS_RS_SPOVERRIDEPLACEMENT			_T("SPOverridePlacement")
#define IDS_RS_SPHORPOS						_T("SPHorPos")
#define IDS_RS_SPVERPOS						_T("SPVerPos")

#define IDS_RS_SPCSIZE						_T("SPCSize")
#define IDS_RS_SPMAXTEXRES					_T("SPMaxTexRes")
#define IDS_RS_SPALLOWANIMATION				_T("SPCAllowAnimationWhenBuffering")
#define IDS_RS_SPALLOWDROPSUBPIC			_T("SPCAllowDropSubPic")

#define IDS_RS_INTREALMEDIA					_T("IntRealMedia")
#define IDS_RS_USEDARKTHEME					_T("UseDarkTheme")

#define IDS_RS_TBREFRESH					_T("Toolbar Refresh")
#define IDS_RS_CLRFACEABGR					_T("Toolbar clrFace(ABGR)")
#define IDS_RS_CLROUTLINEABGR				_T("Toolbar clrOutline(ABGR)")

#define IDS_RS_USEDEDYNAMIC					_T("UseDeDynamic")
#define IDS_RS_DBLCLICKFULLSCREEN			_T("DblClickFullScreen")
#define IDS_RS_EXITFULLSCREENATTHEEND		_T("ExitFullscreenAtTheEnd")
#define IDS_RS_EXITFULLSCREENATFOCUSLOST	_T("ExitFullscreenAtFocusLost")
#define IDS_RS_RESTORERESAFTEREXIT			_T("RestoreResAfterExit")
#define IDS_RS_AUTOSPEAKERCONF				_T("AutoSpeakerConf")
#define IDS_RS_CLOSEDCAPTIONS				_T("ClosedCaptions")
#define IDS_RS_REMEMBERWINDOWPOS			_T("RememberWindowPos")
#define IDS_RS_LASTWINDOWRECT				_T("LastWindowRect")
#define IDS_RS_AUDIORENDERERTYPE			_T("AudioRendererType")
#define IDS_RS_SECONDAUDIORENDERER			_T("SecondAudioRenderer")
#define IDS_RS_DUALAUDIOOUTPUT				_T("DualAudioOtput")
#define IDS_RS_HIDECAPTIONMENU				_T("HideCaptionMenu")
#define IDS_RS_HIDENAVIGATION				_T("HideNavigation")
#define IDS_RS_DEFAULTVIDEOFRAME			_T("DefaultVideoFrame")
#define IDS_RS_REMEMBERWINDOWSIZE			_T("RememberWindowSize")
#define IDS_RS_PANSCANZOOM					_T("PanScanZoom")
#define IDS_RS_AUDIOTIMESHIFT				_T("AudioTimeShift")
#define IDS_RS_SUBDELAYINTERVAL				_T("SubDelayInterval")
#define IDS_RS_ENABLEAUDIOTIMESHIFT			_T("EnableAudioTimeShift")
#define IDS_RS_LOGOFILE						_T("LogoFile")
#define IDS_RS_ENABLEWORKERTHREADFOROPENING	_T("EnableWorkerThreadForOpening")
#define IDS_RS_PNSPRESETS					_T("PnSPresets")
#define IDS_RS_AUTOLOADAUDIO				_T("AutoloadAudio")
#define IDS_RS_PRIORITIZEEXTERNALAUDIO		_T("PrioritizeExternalAudio")
#define IDS_RS_AUDIOPATHS					_T("AudioPaths")
#define IDS_RS_SUBTITLERENDERER				_T("SubtitleRenderer")
#define IDS_RS_SUBTITLESLANGORDER			_T("SubtitlesLanguageOrder")
#define IDS_RS_AUDIOSLANGORDER				_T("AudiosLanguageOrder")
#define IDS_RS_INTERNALSELECTTRACKLOGIC		_T("UseInternalSelectTrackLogic")
#define IDS_RS_SEARCHKEYFRAMES				_T("SearchKeyframes")
#define IDS_RS_ACCELTBL						_T("AccelTbl")
#define IDS_RS_SETFULLSCREENRES				_T("SetFullscreenRes")
#define IDS_RS_FULLSCREENRES				_T("FullscreenRes")
#define IDS_RS_WINLIRCADDR					_T("WinLircAddr")
#define IDS_RS_WINLIRC						_T("UseWinLirc")
#define IDS_RS_TRAYICON						_T("TrayIcon")
#define IDS_RS_KEEPASPECTRATIO				_T("KeepAspectRatio")
#define IDS_RS_UICEADDR						_T("UICEAddr")
#define IDS_RS_UICE							_T("UseUICE")
#define IDS_RS_JUMPDISTS					_T("JumpDistS")
#define IDS_RS_JUMPDISTM					_T("JumpDistM")
#define IDS_RS_JUMPDISTL					_T("JumpDistL")
#define IDS_RS_REPORTFAILEDPINS				_T("ReportFailedPins")
#define IDS_RS_RTSPHANDLER					_T("RtspHandler")
#define IDS_RS_RTSPFILEEXTFIRST				_T("RtspFileExtFirst")
#define IDS_RS_SRCFILTERS					_T("SrcFilters")
#define IDS_RS_KEEPHISTORY					_T("KeepHistory")
#define IDS_RS_RECENT_FILES_NUMBER			_T("RecentFilesNumber")
#define IDS_RS_LOGOID						_T("LogoID2")
#define IDS_RS_LOGOEXT						_T("LogoExt")
#define IDS_RS_TRAFILTERS					_T("TraFilters")
#define IDS_RS_MPEGDI						_T("MPEGDI")
#define IDS_RS_MPEGBRIGHT					_T("MPEGBright")
#define IDS_RS_MPEGCONT						_T("MPEGCont")
#define IDS_RS_MPEGHUE						_T("MPEGHue")
#define IDS_RS_MPEGSAT						_T("MPEGSat")
#define IDS_RS_MPEGFORCEDSUBS				_T("MPEGForcedSubs")
#define IDS_RS_MPEGPLANARYUV				_T("MPEGPlanarYUV")
#define IDS_RS_COMPMONDESKARDIFF			_T("CompMonDeskARDiff")
#define IDS_RS_HIDECDROMSSUBMENU			_T("HideCDROMsSubMenu")
#define IDS_RS_VMRTEXTURE					_T("VMRTexture")
#define IDS_RS_VMR3D						_T("VMR3D")
#define IDS_RS_DSVIDEORENDERERTYPE			_T("DSVidRen")
#define IDS_RS_SHUFFLEPLAYLISTITEMS			_T("ShufflePlaylistItems")
#define IDS_RS_REMEMBERPLAYLISTITEMS		_T("RememberPlaylistItems")
#define IDS_RS_HIDEPLAYLISTFULLSCREEN		_T("HidePlaylistFullScreen")
#define IDS_RS_APSURACEFUSAGE				_T("APSurfaceUsage")
#define IDS_RS_ENABLEWEBSERVER				_T("EnableWebServer")
#define IDS_RS_WEBSERVERPORT				_T("WebServerPort")
#define IDS_RS_WEBSERVERQUALITY				_T("WebServerQuality")
#define IDS_RS_LASTWINDOWTYPE				_T("LastWindowType")
#define IDS_RS_ONTOP						_T("OnTop")
#define IDS_RS_MPASF						_T("MPASampleFormat")
#define IDS_RS_AC3SC						_T("AC3SpeakerConfig")
#define IDS_RS_AC3DRC						_T("AC3DynamicRangeControl")
#define IDS_RS_WEBSERVERPRINTDEBUGINFO		_T("WebServerPrintDebugIfo")
#define IDS_RS_WEBSERVERUSECOMPRESSION		_T("WebServerUseCompression")
#define IDS_RS_MPANORMALIZE					_T("MPANormalize")
#define IDS_RS_DTSSC						_T("DTSSpeakerConfig")
#define IDS_RS_DTSDRC						_T("DTSDynamicRangeControl")
#define IDS_RS_SNAPSHOTPATH					_T("SnapShotPath")
#define IDS_RS_PRIORITY						_T("Priority")
#define IDS_RS_SNAPSHOTEXT					_T("SnapShotExt")
#define IDS_RS_LAUNCHFULLSCREEN				_T("LaunchFullScreen")
#define IDS_RS_MPABOOST						_T("MpaBoost")
#define IDS_RS_AACSC						_T("AACSpeakerConfig")
#define IDS_RS_ISDB							_T("ISDb")
#define IDS_RS_WEBROOT						_T("WebRoot")
#define IDS_RS_WEBSERVERLOCALHOSTONLY		_T("WebServerLocalhostOnly")
#define IDS_RS_ASPECTRATIO_X				_T("AspectRatioX")
#define IDS_RS_ASPECTRATIO_Y				_T("AspectRatioY")
#define IDS_RS_DX9_10BITOUTPUT				_T("DX9TenBitOutput")
#define IDS_RS_DX9_SURFACEFORMAT			_T("DX9SurfaceFormat")
#define IDS_RS_DX9_RESIZER					_T("DX9Resizer")
#define IDS_RS_WEBSERVERCGI					_T("WebServerCGI")
#define IDS_RS_WEBDEFINDEX					_T("WebDefIndex")
#define IDS_RS_LIMITWINDOWPROPORTIONS		_T("LimitWindowProportions")
#define IDS_RS_LASTUSEDPAGE					_T("LastUsedPage")
#define IDS_RS_VMRMIXERMODE					_T("VMRMixerMode")
#define IDS_RS_VMRMIXERYUV					_T("VMRMixerYUV")
#define IDS_RS_THUMBROWS					_T("ThumbRows")
#define IDS_RS_THUMBCOLS					_T("ThumbCols")
#define IDS_RS_THUMBQUALITY					_T("ThumbQuality")
#define IDS_RS_THUMBLEVELPNG				_T("ThumbLevelPNG")
#define IDS_RS_ENABLEEDLEDITOR				_T("EnableEDLEditor")
#define IDS_RS_SHADERLISTSCREENSPACE		_T("ShaderListScreenSpace")
#define IDS_RS_FULLSCREENMONITOR			_T("FullScreenMonitor")
#define IDS_RS_MPC_PREVENT_MINIMIZE			_T("PreventMinimize")
#define IDS_RS_MPC_WIN7TASKBAR				_T("UseWin7TaskBar")
#define IDS_RS_MPC_EXIT_AFTER_PB			_T("ExitAfterPlayBack")
#define IDS_RS_MPC_NEXT_AFTER_PB			_T("SearchInDirAfterPlayBack")
#define IDS_RS_MPC_NEXT_AFTER_PB_LOOPED		_T("SearchInDirAfterPlayBackLooped")
#define IDS_RS_MPC_NO_SEARCH_IN_FOLDER		_T("DontUseSearchInFolder")
#define IDS_RS_USE_TIME_TOOLTIP				_T("UseTimeTooltip")
#define IDS_RS_TIME_TOOLTIP_POSITION		_T("TimeTooltipPosition")
#define IDS_RS_MPC_OSD_SIZE					_T("OSD_Size")
#define IDS_RS_MPC_OSD_FONT					_T("OSD_Font")
#define IDS_RS_LAST_OPEN_DIR				_T("LastOpenDir")
#define IDS_RS_LAST_SAVED_PLAYLIST_DIR		_T("LastSavedPlaylistDir")
#define IDS_RS_ASSOCIATED_WITH_ICON			_T("AssociatedWithIcon")

#define IDS_RS_TOGGLESHADER					_T("ToggleShader")
#define IDS_RS_TOGGLESHADERSSCREENSPACE		_T("ToggleShaderScreenSpace")

#define IDS_RS_DEFAULT_CAPTURE				_T("DefaultCapture")
#define IDS_R_CAPTURE						_T("Capture")
#define IDS_RS_VIDEO_DISP_NAME				_T("VidDispName")
#define IDS_RS_AUDIO_DISP_NAME				_T("AudDispName")
#define IDS_RS_COUNTRY						_T("Country")

#define IDS_R_DVB							_T("DVB configuration")
#define IDS_RS_BDA_NETWORKPROVIDER			_T("BDANetworkProvider")
#define IDS_RS_BDA_TUNER					_T("BDATuner")
#define IDS_RS_BDA_RECEIVER					_T("BDAReceiver")
#define IDS_RS_BDA_STANDARD					_T("BDAStandard")
#define IDS_RS_BDA_SCAN_FREQ_START			_T("BDAScanFreqStart")
#define IDS_RS_BDA_SCAN_FREQ_END			_T("BDAScanFreqEnd")
#define IDS_RS_BDA_BANDWIDTH				_T("BDABandWidth")
#define IDS_RS_BDA_USE_OFFSET				_T("BDAUseOffset")
#define IDS_RS_BDA_OFFSET					_T("BDAOffset")
#define IDS_RS_BDA_IGNORE_ENCRYPTED_CHANNELS _T("BDAIgnoreEncryptedChannels")
#define IDS_RS_DVB_LAST_CHANNEL				_T("LastChannel")

#define IDS_RS_D3D9RENDERDEVICE				_T("D3D9RenderDevice")

#define IDS_RS_FASTSEEK_KEYFRAME			_T("FastSeek")
#define IDS_RS_MINI_DUMP					_T("MiniDump")

#define IDS_RS_LCD_SUPPORT					_T("LcdSupport")
#define IDS_RS_SMARTSEEK					_T("UseSmartSeek")
#define IDS_RS_CHAPTER_MARKER				_T("ChapterMarker")

#define IDS_RS_REMAINING_TIME				_T("RemainingTime")

#define IDS_RS_GOTO_LAST_USED				_T("gotoluf")
#define IDS_RS_GOTO_FPS						_T("fps")

#define IDS_RS_SHADERS_INITIALIZED			_T("Initialized")

#define IDS_R_DLG_SUBTITLEDL				_T("Dialogs\\SubtitleDl")
#define IDS_RS_DLG_SUBTITLEDL_COLWIDTH		_T("ColWidth")

#define IDS_R_DLG_ORGANIZE_FAV				_T("Dialogs\\OrganizeFavorites")

#define IDS_RS_USE_FLYBAR					_T("UseFlybar")
#define IDS_RS_USE_FLYBAR_ONTOP				_T("UseFlybarOnTop")

#define IDS_RS_LAST_OPEN_FILTER_DIR			_T("LastOpenFilterDir")

#define IDS_RS_YOUTUBE_TAG					_T("YoutubeTag")
#define IDS_RS_YOUTUBE_LOAD_PLAYLIST		_T("YoutubeLoadPlaylist")
#define IDS_RS_YOUTUBE_SOURCE				_T("YoutubeSourceType")
#define IDS_RS_YOUTUBE_MEMTYPE				_T("YoutubeMemoryType")
#define IDS_RS_YOUTUBE_PERCENT_MEM			_T("YoutubePercentMemory")
#define IDS_RS_YOUTUBE_MB_MEM				_T("YoutubeMbMemory")

#define IDS_R_PERFOMANCE					_T("\\Perfomance")
#define IDS_RS_PERFOMANCE_CACHE_LENGTH		_T("CacheLen")
#define IDS_RS_PERFOMANCE_MINQUEUESIZE		_T("MinQueueSize")
#define IDS_RS_PERFOMANCE_MAXQUEUESIZE		_T("MaxQueueSize")
#define IDS_RS_PERFOMANCE_MINQUEUEPACKETS	_T("MinQueuePackets")
#define IDS_RS_PERFOMANCE_MAXQUEUEPACKETS	_T("MaxQueuePackets")

#define IDS_R_FILTERS_PRIORITY				_T("\\Filters Priority")

#define IDS_RS_LASTFILEINFOPAGE				_T("LastFileInfoPage")

#define IDS_R_UPDATER						IDS_R_SETTINGS _T("\\Updater")
#define IDS_RS_UPDATER_AUTO_CHECK			_T("UpdaterAutoCheck")
#define IDS_RS_UPDATER_DELAY				_T("UpdaterDelay")
#define IDS_RS_UPDATER_LAST_CHECK			_T("UpdaterLastCheck")

#define IDS_RS_CONTEXTFILES					_T("ShowContextFiles")
#define IDS_RS_CONTEXTDIR					_T("ShowContextDir")
