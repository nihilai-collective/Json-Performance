
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 752.799 | 0.294557 | 7476.42ms | 461466 | 40 | 1.1861e+08 | 584602 | 0.0235147 | 3.28858 | 1(Win) | true |
| Jsonifier (two-stage) | 701.182 | 0.21249 | 8171.39ms | 461466 | 40 | 7.1147e+07 | 627638 | 0.0375607 | 3.53075 | 2(Loss) | true |
| Glaze | 616.591 | 0.124203 | 9162.75ms | 461466 | 160 | 1.25738e+08 | 713744 | 0.316511 | 4.0151 | 3(Loss) | true |
| simdjson (ondemand) | 552.533 | 0.352826 | 5344.17ms | 461466 | 40 | 3.15897e+08 | 796492 | 1.76138 | 4.48068 | 4(Loss) | true |
