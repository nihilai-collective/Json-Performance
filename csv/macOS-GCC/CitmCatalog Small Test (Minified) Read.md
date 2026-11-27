
----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1163.75 | 0.443608 | 268.268ms | 3223 | 2560 | 351432 | 2641.2 | 0.997076 | 1(Win) | true |
| Jsonifier (two-stage) | 1018.59 | 0.211882 | 308.462ms | 3223 | 640 | 26163.1 | 3017.6 | 0.0795967 | 2(Loss) | true |
| Glaze | 946.567 | 0.787723 | 337.259ms | 3223 | 320 | 209370 | 3247.2 | 0.0739645 | 3(Loss) | true |
| simdjson (reflection) | 886.813 | 0.638796 | 351.378ms | 3223 | 640 | 313734 | 3466 | 0.266142 | 4(Loss) | true |
| simdjson (ondemand) | 849.133 | 0.405721 | 385.915ms | 3223 | 1280 | 276080 | 3619.8 | 0.55 | 5(Loss) | true |
