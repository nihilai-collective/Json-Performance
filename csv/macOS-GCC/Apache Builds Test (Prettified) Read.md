
----
### Apache Builds Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1179.63 | 0.354326 | 5197.08ms | 124597 | 2560 | 3.26116e+08 | 100731 | 0.222968 | 1(Win) | true |
| Jsonifier (two-stage) | 1165.76 | 0.224436 | 5283.08ms | 124597 | 1280 | 6.69878e+07 | 101930 | 0.405687 | 2(Loss) | true |
| Glaze | 1132.38 | 0.282105 | 5445.14ms | 124597 | 1280 | 1.12166e+08 | 104934 | 1.28061 | 3(Loss) | true |
| simdjson (reflection) | 1074.8 | 0.140913 | 5741.34ms | 124597 | 2560 | 6.21301e+07 | 110556 | 0.193216 | 4(Loss) | true |
| simdjson (ondemand) | 894.012 | 0.699254 | 6933.16ms | 124597 | 80 | 6.91016e+07 | 132912 | 0.0650477 | 5(Loss) | true |
