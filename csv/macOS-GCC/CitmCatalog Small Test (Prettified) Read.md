
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1862.87 | 0.230079 | 301.456ms | 5839 | 2560 | 121089 | 2989.2 | 0.201126 | 1(Win) | true |
| Jsonifier (two-stage) | 1663.47 | 0.231736 | 346.062ms | 5839 | 4890 | 294269 | 3347.53 | 0.0725598 | 2(Loss) | true |
| simdjson (reflection) | 1489.7 | 0.542211 | 377.225ms | 5839 | 640 | 262903 | 3738 | 0.0107021 | 3(Loss) | true |
| simdjson (ondemand) | 1403.71 | 0.291655 | 402.852ms | 5839 | 1280 | 171346 | 3967 | 1.08552 | 4(Loss) | true |
| Glaze | 1354.18 | 0.148408 | 415.227ms | 5839 | 4890 | 182114 | 4112.07 | 0.18516 | 5(Loss) | true |
