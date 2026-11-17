
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 984.235 | 0.363711 | 5075.91ms | 461466 | 40 | 1.05792e+08 | 447138 | 0.133063 | 1(Win) | true |
| Jsonifier (two-stage) | 832.905 | 2.01454 | 6260.16ms | 461466 | 30 | 3.39909e+09 | 528378 | 0.650257 | 2(Loss) | true |
| Glaze | 792.246 | 0.114844 | 7075.03ms | 461466 | 640 | 2.60471e+08 | 555495 | 0.414806 | 3(Loss) | true |
| simdjson (ondemand) | 575.747 | 0.467534 | 9660.93ms | 461466 | 320 | 4.08689e+09 | 764378 | 3.54433 | 4(Loss) | true |
