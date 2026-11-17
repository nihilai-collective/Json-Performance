
----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 34667.5 | 0.0585295 | 379.687ms | 136037 | 30 | 143.926 | 3742.27 | 0.123658 | 0.0709001 | 1(Win) | true |
| Glaze | 6416.57 | 0.161191 | 2039.08ms | 136076 | 1280 | 1.36034e+06 | 20224.6 | 0.683405 | 0.385345 | 2(Loss) | true |
| simdjson (reflection) | 598.848 | 0.055714 | 5555.23ms | 136037 | 1280 | 1.86475e+07 | 216641 | 0.303613 | 4.13365 | 3(Loss) | true |
