
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1337.02 | 0.0991674 | 410.257ms | 4630 | 40 | 429.026 | 3302.5 | 0.420637 | 1.83752 | 1(Win) | true |
| Jsonifier (two-stage) | 1207.62 | 0.139207 | 442.184ms | 4630 | 4890 | 126688 | 3656.37 | 0.19588 | 2.03537 | 2(Loss) | true |
| Glaze | 905.395 | 0.11022 | 575.562ms | 4630 | 4890 | 141292 | 4876.89 | 0.78339 | 2.72013 | 3(Loss) | true |
| simdjson (ondemand) | 833.705 | 0.122605 | 611.453ms | 4630 | 40 | 1686.6 | 5296.25 | 0.0425009 | 2.95418 | 4(Loss) | true |
