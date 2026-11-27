
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2828.47 | 0.059358 | 5288.08ms | 500299 | 1280 | 1.28329e+07 | 168686 | 0.267071 | 1.7921 | 8.69672 | 1.64055 | 0.00757235 | 0.0054982 | 1.32796e-05 | 1(Win) | true |
| Glaze | 2155.33 | 0.164494 | 6839.46ms | 500299 | 160 | 2.12153e+07 | 221368 | 0.0512486 | 2.36395 | 11.3894 | 2.08902 | 0.00941807 | 0.0021267 | 3.05192e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1984.43 | 0.0775235 | 7201.6ms | 500299 | 640 | 2.22348e+07 | 240433 | 0.053942 | 2.54344 | 12.2645 | 2.09793 | 0.0108924 | 0.03341 | 2.00099e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1278.34 | 0.109577 | 5228.47ms | 500299 | 320 | 5.35246e+07 | 373236 | 0.128262 | 3.94123 | 18.0364 | 2.56943 | 0.00875024 | 0.0259814 | 3.86769e-05 | 4(Loss) | true |
