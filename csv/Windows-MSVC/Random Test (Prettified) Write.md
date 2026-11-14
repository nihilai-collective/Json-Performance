
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4103.67 | 0.228321 | 9852.08ms | 837491 | 640 | 1.26383e+08 | 194629 | 0.0558263 | 0.740038 | 1(Win) | true |
| Glaze | 2126.51 | 0.170353 | 9500.42ms | 837491 | 320 | 1.31002e+08 | 375589 | 0.115118 | 1.42839 | 2(Loss) | true |
