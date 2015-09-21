%define ARCH_X86 1
%define HAVE_INLINE_ASM 1
%define HAVE_AMD3DNOW 1
%define HAVE_AMD3DNOWEXT 1
%define HAVE_AVX 1
%define HAVE_AVX2 1
%define HAVE_FMA3 1
%define HAVE_FMA4 1
%define HAVE_MMX 1
%define HAVE_MMXEXT 1
%define HAVE_SSE 1
%define HAVE_SSE2 1
%define HAVE_SSE3 1
%define HAVE_SSE4 1
%define HAVE_SSE42 1
%define HAVE_SSSE3 1
%define HAVE_XOP 1
%define HAVE_CPUNOP 1
%define HAVE_I686 1
%define HAVE_AMD3DNOW_EXTERNAL 1
%define HAVE_AMD3DNOWEXT_EXTERNAL 1
%define HAVE_AVX_EXTERNAL 1
%define HAVE_AVX2_EXTERNAL 1
%define HAVE_FMA3_EXTERNAL 1
%define HAVE_FMA4_EXTERNAL 1
%define HAVE_MMX_EXTERNAL 1
%define HAVE_MMXEXT_EXTERNAL 1
%define HAVE_SSE_EXTERNAL 1
%define HAVE_SSE2_EXTERNAL 1
%define HAVE_SSE3_EXTERNAL 1
%define HAVE_SSE4_EXTERNAL 1
%define HAVE_SSE42_EXTERNAL 1
%define HAVE_SSSE3_EXTERNAL 1
%define HAVE_XOP_EXTERNAL 1
%define HAVE_CPUNOP_EXTERNAL 0
%define HAVE_I686_EXTERNAL 0
%define HAVE_ALTIVEC_EXTERNAL 0
%define HAVE_ARMV5TE_EXTERNAL 0
%define HAVE_ARMV6_EXTERNAL 0
%define HAVE_ARMV6T2_EXTERNAL 0
%define HAVE_ARMV8_EXTERNAL 0
%define HAVE_MMI_EXTERNAL 0
%define HAVE_NEON_EXTERNAL 0
%define HAVE_PPC4XX_EXTERNAL 0
%define HAVE_VSX_EXTERNAL 0
%define HAVE_VFPV3_EXTERNAL 0
%define HAVE_MIPSFPU_EXTERNAL 0
%define HAVE_MIPS32R2_EXTERNAL 0
%define HAVE_MIPSDSPR1_EXTERNAL 0
%define HAVE_MIPSDSPR2_EXTERNAL 0
%define HAVE_AMD3DNOW_INLINE 1
%define HAVE_AMD3DNOWEXT_INLINE 1
%define HAVE_AVX_INLINE 1
%define HAVE_AVX2_INLINE 1
%define HAVE_FMA3_INLINE 1
%define HAVE_FMA4_INLINE 1
%define HAVE_MMX_INLINE 1
%define HAVE_MMXEXT_INLINE 1
%define HAVE_SSE_INLINE 1
%define HAVE_SSE2_INLINE 1
%define HAVE_SSE3_INLINE 1
%define HAVE_SSE4_INLINE 1
%define HAVE_SSE42_INLINE 1
%define HAVE_SSSE3_INLINE 1
%define HAVE_XOP_INLINE 1
%define HAVE_CPUNOP_INLINE 0
%define HAVE_I686_INLINE 0
%define HAVE_ALTIVEC_INLINE 0
%define HAVE_ARMV5TE_INLINE 0
%define HAVE_ARMV6_INLINE 0
%define HAVE_ARMV6T2_INLINE 0
%define HAVE_ARMV8_INLINE 0
%define HAVE_MMI_INLINE 0
%define HAVE_NEON_INLINE 0
%define HAVE_PPC4XX_INLINE 0
%define HAVE_VSX_INLINE 0
%define HAVE_VFPV3_INLINE 0
%define HAVE_MIPSFPU_INLINE 0
%define HAVE_MIPS32R2_INLINE 0
%define HAVE_MIPSDSPR1_INLINE 0
%define HAVE_MIPSDSPR2_INLINE 0

%ifdef ARCH_X86_64
	%define BROKEN_RELOCATIONS 1
	%define ARCH_X86_32 0
	%define ARCH_X86_64 1
	%define HAVE_FAST_64BIT 1
	%define HAVE_FAST_CMOV 1
	%define HAVE_MM_EMPTY 1
	%define HAVE_XMM_CLOBBERS 1
	%define CONFIG_PIC 1
%else
	%define ARCH_X86_32 1
	%define ARCH_X86_64 0
	%define HAVE_FAST_64BIT 0
	%define HAVE_FAST_CMOV 0
	%define HAVE_MM_EMPTY 0
	%define HAVE_XMM_CLOBBERS 0
	%define CONFIG_PIC 0
%endif

%define ARCH_AARCH64 0
%define ARCH_ALPHA 0
%define ARCH_ARM 0
%define ARCH_AVR32 0
%define ARCH_AVR32_AP 0
%define ARCH_AVR32_UC 0
%define ARCH_BFIN 0
%define ARCH_IA64 0
%define ARCH_M68K 0
%define ARCH_MIPS 0
%define ARCH_MIPS64 0
%define ARCH_PARISC 0
%define ARCH_PPC 0
%define ARCH_PPC64 0
%define ARCH_S390 0
%define ARCH_SH4 0
%define ARCH_SPARC 0
%define ARCH_SPARC64 0
%define ARCH_TILEGX 0
%define ARCH_TILEPRO 0
%define ARCH_TOMI 0
%define HAVE_ALTIVEC 0
%define HAVE_ARMV5TE 0
%define HAVE_ARMV6 0
%define HAVE_ARMV6T2 0
%define HAVE_ARMV8 0
%define HAVE_MMI 0
%define HAVE_NEON 0
%define HAVE_PPC4XX 0
%define HAVE_VSX 0
%define HAVE_VFPV3 0
%define HAVE_MIPSFPU 0
%define HAVE_MIPS32R2 0
%define HAVE_MIPSDSPR1 0
%define HAVE_MIPSDSPR2 0
%define HAVE_BIGENDIAN 0
%define HAVE_FAST_UNALIGNED 1
%define CONFIG_FAST_UNALIGNED 1
%define CONFIG_FFT 1
%define CONFIG_FREI0R 0
%define CONFIG_FTRAPV 0
%define HAVE_PTHREADS 0
%define HAVE_W32THREADS 1
%define HAVE_OS2THREADS 0
%define HAVE_AS_DN_DIRECTIVE 0
%define HAVE_AS_FUNC 1
%define HAVE_ATOMICS_GCC 1
%define HAVE_ATOMICS_WIN32 1
%define HAVE_ATOMICS_SUNCC 0
%define HAVE_ATOMIC_CAS_PTR 0
%define HAVE_ATOMICS_NATIVE 1
%define HAVE_ACCESS 1
%define HAVE_ALIGNED_MALLOC 1
%define HAVE_ALIGNED_STACK 1
%define HAVE_ALSA_ASOUNDLIB_H 0
%define HAVE_ALTIVEC_H 0
%define HAVE_ARPA_INET_H 0
%define HAVE_ASM_TYPES_H 0
%define HAVE_INTRINSICS_NEON 0
%define HAVE_ATANF 1
%define HAVE_ATAN2F 1
%define HAVE_CBRT 1
%define HAVE_ATTRIBUTE_MAY_ALIAS 1
%define HAVE_ATTRIBUTE_PACKED 1
%define HAVE_CBRTF 1
%define HAVE_CL_CL_H 0
%define HAVE_CLOCK_GETTIME 0
%define HAVE_CLOSESOCKET 0
%define HAVE_COSF 1
%define HAVE_COMMANDLINETOARGVW 1
%define HAVE_CRYPTGENRANDOM 1
%define HAVE_DCBZL 1
%define HAVE_DCBZL_EXTERNAL 0
%define HAVE_DCBZL_INLINE 0
%define HAVE_DEV_BKTR_IOCTL_BT848_H 0
%define HAVE_DEV_BKTR_IOCTL_METEOR_H 0
%define HAVE_DEV_IC_BT8XX_H 0
%define HAVE_DEV_VIDEO_BKTR_IOCTL_BT848_H 0
%define HAVE_DEV_VIDEO_METEOR_IOCTL_METEOR_H 0
%define HAVE_DLFCN_H 0
%define HAVE_DLOPEN 0
%define HAVE_DOS_PATHS 1
%define HAVE_EBP_AVAILABLE 1
%define HAVE_EBX_AVAILABLE 1
%define HAVE_EXP2 1
%define HAVE_EXP2F 1
%define HAVE_EXPF 1
%define HAVE_FMINF 1
%define HAVE_FAST_CLZ 1
%define HAVE_FCNTL 0
%define HAVE_FLT_LIM 1
%define HAVE_FORK 0
%define HAVE_GETADDRINFO 0
%define HAVE_GETHRTIME 0
%define HAVE_GETOPT 1
%define HAVE_GETPROCESSAFFINITYMASK 1
%define HAVE_GETPROCESSMEMORYINFO 1
%define HAVE_GETPROCESSTIMES 1
%define HAVE_GETSYSTEMTIMEASFILETIME 1
%define HAVE_GETRUSAGE 0
%define HAVE_GETTIMEOFDAY 1
%define HAVE_GLOB 0
%define HAVE_GLXGETPROCADDRESS 0
%define HAVE_GNU_AS 1
%define HAVE_GNU_WINDRES 0
%define HAVE_IBM_ASM 0
%define HAVE_INET_ATON 0
%define HAVE_INLINE_ASM_LABELS 1
%define HAVE_INLINE_ASM_NONLOCAL_LABELS 1
%define HAVE_INLINE_ASM_DIRECT_SYMBOL_REFS 1
%define HAVE_ISATTY 1
%define HAVE_ISINF 1
%define HAVE_ISNAN 1
%define HAVE_JACK_PORT_GET_LATENCY_RANGE 0
%define HAVE_KBHIT 1
%define HAVE_LDBRX 1
%define HAVE_LDBRX_EXTERNAL 0
%define HAVE_LDBRX_INLINE 0
%define HAVE_LDEXPF 1
%define HAVE_LIBDC1394_1 0
%define HAVE_LIBDC1394_2 0
%define HAVE_LLRINT 1
%define HAVE_LLRINTF 1
%define HAVE_LOCAL_ALIGNED_8 1
%define HAVE_LOCAL_ALIGNED_16 1
%define HAVE_LOCAL_ALIGNED_32 1
%define HAVE_SIMD_ALIGN_16 1
%define HAVE_LOCALTIME_R 0
%define HAVE_LOG2 1
%define HAVE_LOG2F 1
%define HAVE_LOG10F 1
%define HAVE_LOONGSON 1
%define HAVE_LOONGSON_EXTERNAL 0
%define HAVE_LOONGSON_INLINE 0
%define HAVE_LRINT 1
%define HAVE_LRINTF 1
%define HAVE_LZO1X_999_COMPRESS 0
%define HAVE_MACH_ABSOLUTE_TIME 0
%define HAVE_MACH_MACH_TIME_H 0
%define HAVE_MACHINE_IOCTL_BT848_H 0
%define HAVE_MACHINE_IOCTL_METEOR_H 0
%define HAVE_MACHINE_RW_BARRIER 0
%define HAVE_MAKEINFO 1
%define HAVE_MALLOC_H 1
%define HAVE_MAPVIEWOFFILE 1
%define HAVE_MEMALIGN 0
%define HAVE_MEMORYBARRIER 1
%define HAVE_MKSTEMP 0
%define HAVE_MMAP 0
%define HAVE_MPROTECT 0
%define HAVE_MSVCRT 0
%define HAVE_NANOSLEEP 0
%define HAVE_OPENJPEG_1_5_OPENJPEG_H 0
%define HAVE_OPENGL_GL3_H 0
%define HAVE_NETINET_SCTP_H 0
%define HAVE_PEEKNAMEDPIPE 1
%define HAVE_POD2MAN 1
%define HAVE_POLL_H 0
%define HAVE_POSIX_MEMALIGN 0
%define HAVE_PRAGMA_DEPRECATED 1
%define HAVE_POWF 1
%define HAVE_PTHREAD_CANCEL 0
%define HAVE_RSYNC_CONTIMEOUT 0
%define HAVE_SARESTART 0
%define HAVE_RDTSC 1
%define HAVE_RINT 1
%define HAVE_ROUND 1
%define HAVE_ROUNDF 1
%define HAVE_SCHED_GETAFFINITY 0
%define HAVE_SDL 0
%define HAVE_SETCONSOLETEXTATTRIBUTE 1
%define HAVE_SETMODE 1
%define HAVE_SETRLIMIT 0
%define HAVE_SINF 1
%define HAVE_SLEEP 1
%define HAVE_SNDIO_H 0
%define HAVE_SOCKLEN_T 0
%define HAVE_SOUNDCARD_H 0
%define HAVE_STRERROR_R 0
%define HAVE_STRUCT_ADDRINFO 0
%define HAVE_STRUCT_GROUP_SOURCE_REQ 0
%define HAVE_STRUCT_IP_MREQ_SOURCE 0
%define HAVE_STRUCT_IPV6_MREQ 0
%define HAVE_STRUCT_POLLFD 0
%define HAVE_STRUCT_RUSAGE_RU_MAXRSS 0
%define HAVE_STRUCT_SOCKADDR_IN6 0
%define HAVE_STRUCT_SOCKADDR_SA_LEN 0
%define HAVE_STRUCT_SOCKADDR_STORAGE 0
%define HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC 0
%define HAVE_STRUCT_V4L2_FRMIVALENUM_DISCRETE 0
%define HAVE_SYMVER 1
%define HAVE_SYMVER_ASM_LABEL 1
%define HAVE_SYMVER_GNU_ASM 0
%define HAVE_SYNC_VAL_COMPARE_AND_SWAP 1
%define HAVE_SYSCONF 0
%define HAVE_SYSCTL 0
%define HAVE_SYS_MMAN_H 0
%define HAVE_SYS_PARAM_H 1
%define HAVE_SYS_RESOURCE_H 0
%define HAVE_SYS_SELECT_H 0
%define HAVE_SYS_SOUNDCARD_H 0
%define HAVE_SYS_TIME_H 1
%define HAVE_SYS_UN_H 0
%define HAVE_SYS_VIDEOIO_H 0
%define HAVE_TERMIOS_H 0
%define HAVE_TEXI2HTML 0
%define HAVE_THREADS 1
%define HAVE_TRUNC 1
%define HAVE_TRUNCF 1
%define HAVE_UNISTD_H 1
%define HAVE_USLEEP 1
%define HAVE_VDPAU_X11 0
%define HAVE_VFP_ARGS 0
%define HAVE_VIRTUALALLOC 1
%define HAVE_WGLGETPROCADDRESS 0
%define HAVE_WINDOWS_H 1
%define HAVE_WINSOCK2_H 0
%define HAVE_XFORM_ASM 0
%define HAVE_XLIB 0
%define CONFIG_DOC 0
%define CONFIG_ICONV 0
%define HAVE_YASM 1
%define CONFIG_DCT 1
%define CONFIG_DWT 0
%define CONFIG_GPL 1
%define CONFIG_VERSION3 1
%define CONFIG_AC3DSP 1
%define CONFIG_AUDIODSP 1
%define CONFIG_BLOCKDSP 1
%define CONFIG_BSWAPDSP 1
%define CONFIG_CABAC 1
%define CONFIG_DVPROFILE 1
%define CONFIG_FDCTDSP 1
%define CONFIG_ERROR_RESILIENCE 1
%define CONFIG_FRAME_THREAD_ENCODER 0
%define CONFIG_GPLV3 1
%define CONFIG_GRAY 1
%define CONFIG_H263DSP 1
%define CONFIG_H264CHROMA 1
%define CONFIG_H264DSP 1
%define CONFIG_H264PRED 1
%define CONFIG_H264QPEL 1
%define CONFIG_HPELDSP 1
%define CONFIG_HARDCODED_TABLES 0
%define CONFIG_HUFFMAN 1
%define CONFIG_HUFFYUVDSP 1
%define CONFIG_HUFFYUVENCDSP 0
%define CONFIG_IDCTDSP 1
%define CONFIG_INTRAX8 1
%define CONFIG_LLAUDDSP 1
%define CONFIG_LLVIDDSP 1
%define CONFIG_LIBXVID 0
%define CONFIG_LPC 0
%define CONFIG_MDCT 1
%define CONFIG_MEMALIGN_HACK 0
%define CONFIG_MEMORY_POISONING 0
%define CONFIG_NEON_CLOBBER_TEST 0
%define CONFIG_ME_CMP 1
%define CONFIG_MPEG_ER 1
%define CONFIG_MPEGAUDIODSP 1
%define CONFIG_MPEGVIDEO 1
%define CONFIG_PIXBLOCKDSP 1
%define CONFIG_QPELDSP 1
%define CONFIG_TPELDSP 1
%define CONFIG_VIDEODSP 1
%define CONFIG_RAISE_MAJOR 0
%define CONFIG_RDFT 1
%define CONFIG_RUNTIME_CPUDETECT 1
%define CONFIG_SMALL 0
%define CONFIG_OPENAL 0
%define CONFIG_OPENCL 0
%define CONFIG_OPENGL 0
%define CONFIG_XLIB 0
%define CONFIG_ZLIB 1
%define CONFIG_DECODERS 1
%define CONFIG_ENCODERS 0
%define CONFIG_SWSCALE 1
%define CONFIG_SWSCALE_ALPHA 1
%define CONFIG_POSTPROC 0
%define CONFIG_8BPS_DECODER 1
%define CONFIG_AASC_DECODER 0
%define CONFIG_AIC_DECODER 1
%define CONFIG_AMV_DECODER 1
%define CONFIG_ASV1_DECODER 0
%define CONFIG_ASV2_DECODER 0
%define CONFIG_AVS_DECODER 0
%define CONFIG_BINK_DECODER 1
%define CONFIG_BRENDER_PIX_DECODER 0
%define CONFIG_CAVS_DECODER 0
%define CONFIG_CINEPAK_DECODER 1
%define CONFIG_CLLC_DECODER 1
%define CONFIG_CSCD_DECODER 1
%define CONFIG_CYUV_DECODER 0
%define CONFIG_DIRAC_DECODER 1
%define CONFIG_DNXHD_DECODER 1
%define CONFIG_DSD_LSBF_DECODER 1
%define CONFIG_DSD_MSBF_DECODER 1
%define CONFIG_DSD_LSBF_PLANAR_DECODER 1
%define CONFIG_DSD_MSBF_PLANAR_DECODER 1
%define CONFIG_DVVIDEO_DECODER 1
%define CONFIG_EIGHTBPS_DECODER 0
%define CONFIG_FFV1_DECODER 1
%define CONFIG_FFVHUFF_DECODER 1
%define CONFIG_FLASHSV_DECODER 1
%define CONFIG_FLASHSV2_DECODER 0
%define CONFIG_FLV_DECODER 1
%define CONFIG_FRAPS_DECODER 1
%define CONFIG_G2M_DECODER 1
%define CONFIG_H261_DECODER 0
%define CONFIG_H263_DECODER 1
%define CONFIG_H263I_DECODER 1
%define CONFIG_H263P_DECODER 1
%define CONFIG_H264_DECODER 1
%define CONFIG_H264_CRYSTALHD_DECODER 0
%define CONFIG_H264_VDA_DECODER 0
%define CONFIG_H264_VDPAU_DECODER 0
%define CONFIG_HEVC_DECODER 1
%define CONFIG_HUFFYUV_DECODER 1
%define CONFIG_IAC_DECODER 1
%define CONFIG_IMC_DECODER 0
%define CONFIG_INDEO2_DECODER 0
%define CONFIG_INDEO3_DECODER 1
%define CONFIG_INDEO4_DECODER 1
%define CONFIG_INDEO5_DECODER 1
%define CONFIG_JPEGLS_DECODER 0
%define CONFIG_LAGARITH_DECODER 1
%define CONFIG_LIBOPENJPEG_DECODER 1
%define CONFIG_LIBOPUS_DECODER 0
%define CONFIG_LIBSPEEX_DECODER 1
%define CONFIG_LIBVPX_VP9_DECODER 0
%define CONFIG_LIBDCADEC_DECODER 1
%define CONFIG_LOCO_DECODER 0
%define CONFIG_MJPEG_DECODER 1
%define CONFIG_MJPEGB_DECODER 1
%define CONFIG_MPEG1VIDEO_DECODER 1
%define CONFIG_MPEG2VIDEO_DECODER 1
%define CONFIG_MPEG4_DECODER 1
%define CONFIG_MPEGVIDEO_DECODER 0
%define CONFIG_MSA1_DECODER 1
%define CONFIG_MSMPEG4V1_DECODER 1
%define CONFIG_MSMPEG4V2_DECODER 1
%define CONFIG_MSMPEG4V3_DECODER 1
%define CONFIG_MSRLE_DECODER 0
%define CONFIG_MSS1_DECODER 1
%define CONFIG_MSS2_DECODER 1
%define CONFIG_MSVIDEO1_DECODER 1
%define CONFIG_MSZH_DECODER 0
%define CONFIG_MTS2_DECODER 1
%define CONFIG_MVC1_DECODER 0
%define CONFIG_MVC2_DECODER 0
%define CONFIG_PNG_DECODER 1
%define CONFIG_APNG_DECODER 0
%define CONFIG_QPEG_DECODER 0
%define CONFIG_QDM2_DECODER 1
%define CONFIG_QTRLE_DECODER 1
%define CONFIG_PRORES_DECODER 1
%define CONFIG_RPZA_DECODER 1
%define CONFIG_RV10_DECODER 1
%define CONFIG_RV20_DECODER 1
%define CONFIG_RV30_DECODER 1
%define CONFIG_RV40_DECODER 1
%define CONFIG_SNOW_DECODER 0
%define CONFIG_SP5X_DECODER 1
%define CONFIG_SVQ1_DECODER 1
%define CONFIG_SVQ3_DECODER 1
%define CONFIG_THEORA_DECODER 1
%define CONFIG_TRUEMOTION1_DECODER 0
%define CONFIG_TRUEMOTION2_DECODER 0
%define CONFIG_TSCC_DECODER 1
%define CONFIG_TSCC2_DECODER 1
%define CONFIG_ULTI_DECODER 0
%define CONFIG_VC1_DECODER 1
%define CONFIG_VC1IMAGE_DECODER 1
%define CONFIG_VCR1_DECODER 0
%define CONFIG_VMNC_DECODER 1
%define CONFIG_VP3_DECODER 1
%define CONFIG_VP5_DECODER 1
%define CONFIG_VP6_DECODER 1
%define CONFIG_VP6A_DECODER 1
%define CONFIG_VP6F_DECODER 1
%define CONFIG_VP7_DECODER 1
%define CONFIG_VP8_DECODER 1
%define CONFIG_VP9_DECODER 1
%define CONFIG_WMV1_DECODER 1
%define CONFIG_WMV2_DECODER 1
%define CONFIG_WMV3_DECODER 1
%define CONFIG_WMV3IMAGE_DECODER 1
%define CONFIG_WNV1_DECODER 0
%define CONFIG_XL_DECODER 0
%define CONFIG_ZLIB_DECODER 0
%define CONFIG_ZMBV_DECODER 0
%define CONFIG_AAC_DECODER 1
%define CONFIG_AAC_LATM_DECODER 1
%define CONFIG_AC3_DECODER 1
%define CONFIG_AC3_FIXED_DECODER 1
%define CONFIG_ALAC_DECODER 1
%define CONFIG_ALS_DECODER 1
%define CONFIG_APE_DECODER 1
%define CONFIG_ATRAC3_DECODER 1
%define CONFIG_ATRAC3P_DECODER 1
%define CONFIG_BINKAUDIO_DCT_DECODER 1
%define CONFIG_BINKAUDIO_RDFT_DECODER 1
%define CONFIG_COOK_DECODER 1
%define CONFIG_DCA_DECODER 0
%define CONFIG_EAC3_DECODER 1
%define CONFIG_FLAC_DECODER 1
%define CONFIG_FLAC_ENCODER 0
%define CONFIG_GSM_DECODER 0
%define CONFIG_GSM_MS_DECODER 0
%define CONFIG_IMC_DECODER 0
%define CONFIG_MACE3_DECODER 0
%define CONFIG_MACE6_DECODER 0
%define CONFIG_METASOUND_DECODER 1
%define CONFIG_MPC7_DECODER 1
%define CONFIG_MPC8_DECODER 1
%define CONFIG_MLP_DECODER 1
%define CONFIG_MP1_DECODER 0
%define CONFIG_MP1FLOAT_DECODER 1
%define CONFIG_MP2_DECODER 0
%define CONFIG_MP2FLOAT_DECODER 1
%define CONFIG_MP3_DECODER 0
%define CONFIG_MP3FLOAT_DECODER 1
%define CONFIG_NELLYMOSER_DECODER 1
%define CONFIG_OPUS_DECODER 1
%define CONFIG_QDM2_DECODER 0
%define CONFIG_RA_144_DECODER 1
%define CONFIG_RA_288_DECODER 1
%define CONFIG_RALF_DECODER 1
%define CONFIG_SHORTEN_DECODER 1
%define CONFIG_SIPR_DECODER 1
%define CONFIG_TAK_DECODER 1
%define CONFIG_TRUEHD_DECODER 1
%define CONFIG_TRUESPEECH_DECODER 1
%define CONFIG_TTA_DECODER 1
%define CONFIG_VORBIS_DECODER 1
%define CONFIG_WAVPACK_DECODER 1
%define CONFIG_WMALOSSLESS_DECODER 1
%define CONFIG_WMAPRO_DECODER 1
%define CONFIG_WMAV1_DECODER 1
%define CONFIG_WMAV2_DECODER 1
%define CONFIG_WMAVOICE_DECODER 1
%define CONFIG_PCM_ALAW_DECODER 0
%define CONFIG_PCM_BLURAY_DECODER 0
%define CONFIG_PCM_DVD_DECODER 0
%define CONFIG_PCM_F32BE_DECODER 0
%define CONFIG_PCM_F32LE_DECODER 0
%define CONFIG_PCM_F64BE_DECODER 0
%define CONFIG_PCM_F64LE_DECODER 0
%define CONFIG_PCM_LXF_DECODER 0
%define CONFIG_PCM_MULAW_DECODER 0
%define CONFIG_PCM_S8_DECODER 0
%define CONFIG_PCM_S8_PLANAR_DECODER 0
%define CONFIG_PCM_S16BE_DECODER 0
%define CONFIG_PCM_S16BE_PLANAR_DECODER 0
%define CONFIG_PCM_S16LE_DECODER 0
%define CONFIG_PCM_S16LE_PLANAR_DECODER 0
%define CONFIG_PCM_S24BE_DECODER 0
%define CONFIG_PCM_S24DAUD_DECODER 0
%define CONFIG_PCM_S24LE_DECODER 0
%define CONFIG_PCM_S24LE_PLANAR_DECODER 0
%define CONFIG_PCM_S32BE_DECODER 0
%define CONFIG_PCM_S32LE_DECODER 0
%define CONFIG_PCM_S32LE_PLANAR_DECODER 0
%define CONFIG_PCM_U8_DECODER 0
%define CONFIG_PCM_U16BE_DECODER 0
%define CONFIG_PCM_U16LE_DECODER 0
%define CONFIG_PCM_U24BE_DECODER 0
%define CONFIG_PCM_U24LE_DECODER 0
%define CONFIG_PCM_U32BE_DECODER 0
%define CONFIG_PCM_U32LE_DECODER 0
%define CONFIG_PCM_ZORK_DECODER 0
%define CONFIG_ADPCM_4XM_DECODER 1
%define CONFIG_ADPCM_ADX_DECODER 1
%define CONFIG_ADPCM_AFC_DECODER 1
%define CONFIG_ADPCM_CT_DECODER 1
%define CONFIG_ADPCM_DTK_DECODER 1
%define CONFIG_ADPCM_EA_DECODER 1
%define CONFIG_ADPCM_EA_MAXIS_XA_DECODER 1
%define CONFIG_ADPCM_EA_R1_DECODER 1
%define CONFIG_ADPCM_EA_R2_DECODER 1
%define CONFIG_ADPCM_EA_R3_DECODER 1
%define CONFIG_ADPCM_EA_XAS_DECODER 1
%define CONFIG_ADPCM_G722_DECODER 0
%define CONFIG_ADPCM_G726_DECODER 0
%define CONFIG_ADPCM_IMA_AMV_DECODER 1
%define CONFIG_ADPCM_IMA_APC_DECODER 1
%define CONFIG_ADPCM_IMA_DK3_DECODER 1
%define CONFIG_ADPCM_IMA_DK4_DECODER 1
%define CONFIG_ADPCM_IMA_EA_EACS_DECODER 1
%define CONFIG_ADPCM_IMA_EA_SEAD_DECODER 1
%define CONFIG_ADPCM_IMA_ISS_DECODER 1
%define CONFIG_ADPCM_IMA_OKI_DECODER 1
%define CONFIG_ADPCM_IMA_QT_DECODER 1
%define CONFIG_ADPCM_IMA_SMJPEG_DECODER 1
%define CONFIG_ADPCM_IMA_WAV_DECODER 1
%define CONFIG_ADPCM_IMA_WS_DECODER 1
%define CONFIG_ADPCM_MS_DECODER 1
%define CONFIG_ADPCM_SBPRO_2_DECODER 1
%define CONFIG_ADPCM_SBPRO_3_DECODER 1
%define CONFIG_ADPCM_SBPRO_4_DECODER 1
%define CONFIG_ADPCM_SWF_DECODER 1
%define CONFIG_ADPCM_THP_DECODER 1
%define CONFIG_ADPCM_XA_DECODER 1
%define CONFIG_ADPCM_YAMAHA_DECODER 1
%define CONFIG_DVVIDEO_ENCODER 0
%define CONFIG_FFV1_ENCODER 0
%define CONFIG_FFVHUFF_ENCODER 0
%define CONFIG_FLV_ENCODER 0
%define CONFIG_H261_ENCODER 0
%define CONFIG_H263_ENCODER 0
%define CONFIG_H263P_ENCODER 0
%define CONFIG_H264_ENCODER 0
%define CONFIG_HUFFYUV_ENCODER 0
%define CONFIG_LJPEG_ENCODER 0
%define CONFIG_MJPEG_ENCODER 0
%define CONFIG_MPEG1VIDEO_ENCODER 0
%define CONFIG_MPEG2VIDEO_ENCODER 0
%define CONFIG_MPEG4_ENCODER 0
%define CONFIG_MSMPEG4V1_ENCODER 0
%define CONFIG_MSMPEG4V2_ENCODER 0
%define CONFIG_MSMPEG4V3_ENCODER 0
%define CONFIG_PNG_ENCODER 0
%define CONFIG_RV10_ENCODER 0
%define CONFIG_RV20_ENCODER 0
%define CONFIG_SNOW_ENCODER 0
%define CONFIG_WMV1_ENCODER 0
%define CONFIG_WMV2_ENCODER 0
%define CONFIG_AC3_ENCODER 1
%define CONFIG_AC3_FIXED_ENCODER 0
%define CONFIG_EAC3_ENCODER 0
%define CONFIG_AAC_PARSER 0
%define CONFIG_AAC_LATM_PARSER 1
%define CONFIG_AC3_PARSER 1
%define CONFIG_ADX_PARSER 1
%define CONFIG_DCA_PARSER 1
%define CONFIG_DNXHD_PARSER 1
%define CONFIG_H263_PARSER 1
%define CONFIG_H264_PARSER 1
%define CONFIG_HEVC_PARSER 1
%define CONFIG_MJPEG_PARSER 1
%define CONFIG_MPEGAUDIO_PARSER 1
%define CONFIG_MPEG4VIDEO_PARSER 1
%define CONFIG_MLP_PARSER 1
%define CONFIG_MPEGVIDEO_PARSER 1
%define CONFIG_TAK_PARSER 1
%define CONFIG_AMRNB_DECODER 1
%define CONFIG_AMRWB_DECODER 1
%define CONFIG_MPEG_XVMC_DECODER 0
%define CONFIG_EATGQ_DECODER 0
%define CONFIG_UTVIDEO_DECODER 1
%define CONFIG_V210_DECODER 1
%define CONFIG_V410_DECODER 1
%define CONFIG_RAWVIDEO_DECODER 1
%define CONFIG_VDPAU 0
%define CONFIG_XVMC 0
%define CONFIG_MPEG1_XVMC_HWACCEL 0
%define CONFIG_MPEG2_XVMC_HWACCEL 0
%define CONFIG_VORBIS_PARSER 1
%define CONFIG_VP3_PARSER 1
%define CONFIG_VP8_PARSER 0
%define CONFIG_VP9_PARSER 0
%define CONFIG_ATEMPO_FILTER 1
%define CONFIG_LOWPASS_FILTER 0
%define CONFIG_YADIF_FILTER 0

%define CONFIG_H264_DXVA2_HWACCEL 0
%define CONFIG_H264_D3D11VA_HWACCEL 0
%define CONFIG_H264_VAAPI_HWACCEL 0
%define CONFIG_H264_VDA_HWACCEL 0
%define CONFIG_H264_VDPAU_HWACCEL 0
%define CONFIG_H264_VIDEOTOOLBOX_HWACCEL 0

%define CONFIG_HEVC_DXVA2_HWACCEL 0
%define CONFIG_HEVC_D3D11VA_HWACCEL 0
%define CONFIG_HEVC_VAAPI_HWACCEL 0
%define CONFIG_HEVC_VDPAU_HWACCEL 0

%define CONFIG_MPEG2_XVMC_HWACCEL 0
%define CONFIG_MPEG_VDPAU_DECODER 0
%define CONFIG_MPEG2_VDPAU_HWACCEL 0
%define CONFIG_MPEG2_DXVA2_HWACCEL 0
%define CONFIG_MPEG2_D3D11VA_HWACCEL 0
%define CONFIG_MPEG2_VAAPI_HWACCEL 0
%define CONFIG_MPEG2_VIDEOTOOLBOX_HWACCEL 0

%define CONFIG_VC1_DXVA2_HWACCEL 0
%define CONFIG_VC1_D3D11VA_HWACCEL 0
%define CONFIG_VC1_VAAPI_HWACCEL 0
%define CONFIG_VC1_VDPAU_HWACCEL 0
