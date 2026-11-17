
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1160.76 | 0.292351 | 9684.83ms | 461466 | 640 | 7.86295e+08 | 379138 | 1.55011 | 2.13267 | 1(Win) | true |
| Jsonifier (two-stage) | 1116.41 | 0.311589 | 5142.06ms | 461466 | 320 | 4.8278e+08 | 394201 | 1.45771 | 2.21741 | 2(Loss) | true |
| Glaze | 1022.09 | 0.120276 | 5449.68ms | 461466 | 320 | 8.58229e+07 | 430575 | 0.0289246 | 2.42204 | 3(Loss) | true |
| simdjson (ondemand) | 796.316 | 0.258499 | 7295.39ms | 461466 | 160 | 3.26547e+08 | 552655 | 1.10902 | 3.10884 | 4(Loss) | true |
