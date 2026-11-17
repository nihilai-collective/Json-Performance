
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3500.32 | 0.234103 | 5960.44ms | 837491 | 640 | 1.82616e+08 | 228177 | 0.372186 | 0.706937 | 1(Win) | true |
| Glaze | 1843.7 | 1.00582 | 5470.3ms | 837491 | 80 | 1.51885e+09 | 433201 | 0.112372 | 1.34246 | 2(Loss) | true |
