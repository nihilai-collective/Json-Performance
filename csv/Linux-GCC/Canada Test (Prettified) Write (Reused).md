
----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5671.94 | 0.0534337 | 7188.9ms | 6661897 | 160 | 5.7317e+07 | 1.12012e+06 | 1.18703 | 0.436491 | 1(Win) | true |
| Glaze | 3403.83 | 0.0609535 | 5873.44ms | 6661897 | 40 | 5.17745e+07 | 1.86651e+06 | 0.357229 | 0.727345 | 2(Loss) | true |
| simdjson (reflection) | 373.554 | 0.152346 | 5236.68ms | 6661989 | 30 | 2.01413e+10 | 1.70079e+07 | 1.17641 | 6.62764 | 3(Loss) | true |
