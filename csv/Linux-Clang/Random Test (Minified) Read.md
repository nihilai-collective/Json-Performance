
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1481.28 | 0.185051 | 7682.91ms | 461466 | 80 | 2.41811e+07 | 297099 | 0.0743012 | 1.67114 | 1(Win) | true |
| Jsonifier (two-stage) | 1190.54 | 0.161435 | 9375.98ms | 461466 | 40 | 1.42445e+07 | 369655 | 0.171596 | 2.07929 | 2(Loss) | true |
| Glaze | 1101.25 | 0.0742454 | 5095.7ms | 461466 | 320 | 2.81706e+07 | 399625 | 0.370876 | 2.24793 | 3(Loss) | true |
| simdjson (ondemand) | 770.205 | 0.079463 | 7243.55ms | 461466 | 640 | 1.3194e+08 | 571391 | 0.167787 | 3.21421 | 4(Loss) | true |
