
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3690.63 | 0.180865 | 8680.89ms | 1151920 | 640 | 1.85495e+08 | 297661 | 0.0485351 | 1(Win) | true |
| Jsonifier (two-stage) | 2999.89 | 0.273695 | 5241.47ms | 1151920 | 30 | 3.01363e+07 | 366199 | 0.0349414 | 2(Loss) | true |
| simdjson (ondemand) | 2450.87 | 0.152844 | 6580.96ms | 1151920 | 30 | 1.40805e+07 | 448230 | 0.550949 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 2204.53 | 0.830955 | 7128.04ms | 1151920 | 80 | 1.37169e+09 | 498317 | 2.67615 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 2194.56 | 0.226973 | 8303.35ms | 1151920 | 30 | 3.87277e+07 | 500582 | 0.667163 | 4(Tie) | true |
