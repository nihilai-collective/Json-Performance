
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1307.22 | 0.859137 | 508.597ms | 8051 | 320 | 814851 | 5873.56 | 0.272937 | 1(Win) | true |
| Glaze | 1279.92 | 0.201391 | 743.075ms | 8051 | 40 | 5838.18 | 5998.85 | 0.111286 | 2(Loss) | true |
| Jsonifier (two-stage) | 1238.38 | 0.364609 | 608.278ms | 8051 | 1280 | 654121 | 6200.07 | 1.53515 | 3(Loss) | true |
| simdjson (ondemand) | 817.537 | 0.497464 | 909.803ms | 8051 | 640 | 1.39697e+06 | 9391.67 | 0.781429 | 4(Loss) | true |
