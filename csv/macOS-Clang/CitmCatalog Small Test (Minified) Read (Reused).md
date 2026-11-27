
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1921.96 | 0.0556164 | 216.802ms | 3223 | 640 | 506.314 | 1599.25 | 0.0698081 | 1(Win) | true |
| Jsonifier (two-stage) | 1422.04 | 0.0569639 | 273.933ms | 3223 | 320 | 485.115 | 2161.46 | 0.0248736 | 2(Loss) | true |
| Glaze | 1169.04 | 0.264407 | 315.174ms | 3223 | 40 | 1933.17 | 2629.25 | 0.117408 | 3(Loss) | true |
| simdjson (ondemand) | 872.223 | 0.112651 | 405.341ms | 3223 | 160 | 2521.47 | 3523.97 | 0.174215 | 4(Loss) | true |
