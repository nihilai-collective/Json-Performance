
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8127.65 | 0.0537921 | 765.842ms | 3223 | 2560 | 105.942 | 378.177 | 0.0630475 | 0.690017 | 1.97642 | 0.319888 | 0.000310634 | 4.64193e-05 | 2.23007e-05 | 1(Win) | true |
| simdjson (reflection) | 6604.76 | 0.673899 | 775.453ms | 3223 | 40 | 393.42 | 465.375 | 0.05548 | 0.848208 | 2.52249 | 0.283276 | 0.000318027 | 0.000279243 | 0.000124108 | 2(Loss) | true |
| Glaze | 4086.11 | 0.174321 | 804.487ms | 3223 | 640 | 1100.48 | 752.23 | 0.504476 | 1.31418 | 4.40242 | 0.633571 | 0.000312209 | 4.65405e-05 | 2.23007e-05 | 3(Loss) | true |
