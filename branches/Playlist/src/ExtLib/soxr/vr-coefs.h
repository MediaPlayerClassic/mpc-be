/* SoX Resampler Library      Copyright (c) 2007-16 robs@users.sourceforge.net
 * Licence for this file: LGPL v2.1                  See LICENCE for details. */

static float const half_fir_coefs[] = {
 0.471112154f,  0.316907549f,  0.0286963396f, -0.101927032f,
-0.0281272982f,  0.0568029535f,  0.027196876f, -0.0360795942f,
-0.0259313561f,  0.023641162f,  0.0243660538f, -0.0151238564f,
-0.0225440668f,  0.00886927471f,  0.0205146088f, -0.00411434209f,
-0.0183312132f,  0.000458525335f,  0.0160497772f,  0.00233248286f,
-0.0137265989f, -0.0044106884f,  0.011416442f,  0.005885487f,
-0.00917074467f, -0.00684373006f,  0.00703601669f,  0.00736018933f,
-0.00505250698f, -0.00750298261f,  0.00325317131f,  0.00733618346f,
-0.00166298445f, -0.00692082025f,  0.000298598848f,  0.00631493711f,
 0.000831644129f, -0.0055731438f, -0.00172737872f,  0.00474591812f,
 0.0023955814f, -0.0038788491f, -0.00284969263f,  0.00301194082f,
 0.00310854264f, -0.00217906496f, -0.00319514679f,  0.00140761062f,
 0.00313542959f, -0.000718361916f, -0.00295694328f,  0.000125607323f,
 0.00268763625f,  0.000362527878f, -0.00235472525f, -0.000743552559f,
 0.00198371228f,  0.00101991741f, -0.0015975797f, -0.00119820218f,
 0.00121618271f,  0.0012882279f, -0.000855849209f, -0.00130214036f,
 0.000529184474f,  0.00125350876f, -0.000245067778f, -0.00115647977f,
 8.82118676e-06f,  0.00102502052f,  0.000177478031f, -0.000872275256f,
-0.000314572995f,  0.000710055602f,  0.000405526007f, -0.000548470439f,
-0.000455174442f,  0.000395698685f,  0.000469579667f, -0.000257895884f,
-0.000455495078f,  0.000139222702f,  0.000419883982f, -4.19753541e-05f,
-0.00036950051f, -3.32020844e-05f,  0.000310554015f,  8.7050045e-05f,
-0.000248456595f, -0.000121389974f,  0.000187662656f,  0.000138813233f,
-0.000131587954f, -0.000142374865f,  8.26090549e-05f,  0.000135318039f,
-4.21208043e-05f, -0.000120830917f,  1.06505085e-05f,  0.00010185819f,
 1.20015129e-05f, -8.09558888e-05f, -2.65925299e-05f,  6.02101571e-05f,
 3.42775752e-05f, -4.11911155e-05f, -3.64462477e-05f,  2.49654252e-05f,
 3.46090513e-05f, -1.21078107e-05f, -3.03027209e-05f,  2.73562006e-06f,
 2.51329043e-05f,  3.66157998e-06f, -2.0990973e-05f, -9.38752332e-06f,
 2.07133365e-05f,  3.2060847e-05f,  1.98462364e-05f,  4.90328648e-06f,
-5.28550107e-07f,
};

static float const fast_half_fir_coefs[] = {
 0.309418476f, -0.0819805418f,  0.0305513441f, -0.0101582224f,
 0.00251293175f, -0.000346895324f,
};

static float const coefs0_d[] = {
 0.f, 1.40520362e-05f,  2.32939994e-05f,  4.00699869e-05f,  6.18938797e-05f,
 8.79406317e-05f,  0.000116304226f,  0.000143862785f,  0.000166286173f,
 0.000178229431f,  0.00017374107f,  0.00014689118f,  9.25928444e-05f,
 7.55567388e-06f, -0.000108723934f, -0.000253061416f, -0.000417917952f,
-0.000591117466f, -0.000756082504f, -0.000892686881f, -0.000978762367f,
-0.000992225841f, -0.00091370246f, -0.000729430325f, -0.000434153678f,
-3.36489703e-05f,  0.000453499646f,  0.000995243588f,  0.00154683724f,
 0.00205322353f,  0.00245307376f,  0.0026843294f,  0.0026908874f,
 0.00242986868f,  0.00187874742f,  0.00104150259f, -4.70759945e-05f,
-0.00131972748f, -0.00267834298f, -0.00399923407f, -0.00514205849f,
-0.00596200535f, -0.00632441105f, -0.00612058374f, -0.00528328869f,
-0.00380015804f, -0.0017232609f,  0.000826765169f,  0.0036632503f,
 0.00654337507f,  0.00918536843f,  0.0112922007f,  0.0125801323f,
 0.0128097433f,  0.0118164904f,  0.00953750551f,  0.00603133188f,
 0.00148762708f, -0.00377544588f, -0.009327395f, -0.014655127f,
-0.0192047839f, -0.0224328082f, -0.0238620596f, -0.0231377935f,
-0.0200777417f, -0.0147104883f, -0.00729690011f,  0.0016694689f,
 0.0114853672f,  0.02128446f,  0.0301054204f,  0.03697694f,
 0.0410129138f,  0.0415093321f,  0.0380333749f,  0.0304950299f,
 0.0191923285f,  0.00482304203f, -0.0115416941f, -0.0285230397f,
-0.0445368533f, -0.0579264573f, -0.0671158215f, -0.070770308f,
-0.0679502076f, -0.0582416438f, -0.0418501969f, -0.0196448429f,
 0.00685658762f,  0.0355644891f,  0.0639556622f,  0.0892653703f,
 0.108720484f,  0.11979613f,  0.120474745f,  0.109484562f,
 0.0864946948f,  0.0522461633f,  0.00860233712f, -0.041491734f,
-0.0941444939f, -0.144742955f, -0.188255118f, -0.219589829f,
-0.233988169f, -0.227416437f, -0.196929062f, -0.140970726f,
-0.0595905561f,  0.0454527813f,  0.170708227f,  0.311175511f,
 0.460568159f,  0.61168037f,  0.756833088f,  0.888367707f,
 0.999151395f,  1.08305644f,  1.13537741f,  1.15315438f,
};

static float const coefs0_u[] = {
 0.f, 2.4378013e-05f,  9.70782157e-05f,  0.000256572953f,  0.000527352928f,
 0.000890796838f,  0.00124949518f,  0.00140604793f,  0.00107945998f,
-2.15586031e-05f, -0.00206589462f, -0.00493342625f, -0.00807135101f,
-0.0104515787f, -0.0107039866f, -0.00746258988f,  0.000109078838f,
 0.0117345872f,  0.0255795186f,  0.0381690155f,  0.0448461522f,
 0.0408218138f,  0.0226797758f, -0.00999595371f, -0.0533441602f,
-0.0987927774f, -0.133827418f, -0.144042973f, -0.116198269f,
-0.0416493482f,  0.0806808506f,  0.242643854f,  0.427127981f,
 0.610413245f,  0.766259257f,  0.8708884f,  0.907742029f,
};

static float const iir_coefs[] = {
 0.0262852045f,  0.0998310478f,  0.206865061f,  0.330224134f,
 0.454420362f,  0.568578357f,  0.666944466f,  0.747869771f,
 0.812324404f,  0.8626001f,  0.901427744f,  0.931486057f,
 0.955191529f,  0.974661783f,  0.991776305f,
};
