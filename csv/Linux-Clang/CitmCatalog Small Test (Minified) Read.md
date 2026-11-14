
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1639.02 | 0.154301 | 923.799ms | 3223 | 2560 | 21435.2 | 1875.32 | 0.151996 | 3.15083 | 11.9299 | 2.25225 | 0.00115273 | 5.42972e-05 | 1.40591e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1370.4 | 0.213127 | 960.404ms | 3223 | 1280 | 29249.3 | 2242.92 | 0.321658 | 3.72829 | 14.6758 | 2.58672 | 0.00111067 | 4.48437e-05 | 2.42398e-06 | 2(Loss) | true |
| Glaze | 1334.94 | 0.109539 | 967.567ms | 3223 | 4890 | 31106.1 | 2302.5 | 0.11067 | 3.85345 | 15.0828 | 2.86658 | 0.00148428 | 6.86528e-05 | 1.40224e-05 | 3(Loss) | true |
| simdjson (ondemand) | 975.319 | 0.236198 | 1055.93ms | 3223 | 40 | 2216.36 | 3151.47 | 0.0193069 | 5.25323 | 19.4729 | 3.17251 | 0.0028157 | 0.000139621 | 5.42972e-05 | 4(Loss) | true |
