
----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16396.5 | 1.84295 | 56.1001ms | 9255 | 2560 | 251951 | 538.3 | 0.20393 | 1(Win) | true |
| Glaze | 2976.61 | 0.21877 | 320.496ms | 9255 | 2560 | 107727 | 2965.2 | 0.345178 | 2(Loss) | true |
| simdjson (reflection) | 330.958 | 0.35294 | 2920ms | 9255 | 160 | 1.41751e+06 | 26668.8 | 0.542888 | 3(Loss) | true |
