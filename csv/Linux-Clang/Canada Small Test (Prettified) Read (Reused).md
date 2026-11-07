
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2764.98 | 0.0822517 | 492.416ms | 11579 | 30 | 323.72 | 3993.73 | 0.0992237 | 0.889714 | 1(Win) | true |
| Jsonifier | 2498.17 | 0.0564242 | 549.551ms | 11579 | 30 | 186.616 | 4420.27 | 0.339696 | 0.985439 | 2(Loss) | true |
| simdjson (ondemand) | 1875.82 | 0.190814 | 678.872ms | 11579 | 2560 | 323014 | 5886.8 | 0.274797 | 1.31336 | 3(Loss) | true |
| Glaze | 1814.86 | 0.0492974 | 712.717ms | 11579 | 30 | 269.913 | 6084.53 | 0.157529 | 1.35855 | 4(Loss) | true |
