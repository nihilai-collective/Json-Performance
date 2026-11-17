
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2315.85 | 0.111104 | 5151.92ms | 94653 | 640 | 1.20029e+06 | 38978.3 | 0.0116758 | 1.06831 | 1(Win) | true |
| Jsonifier (two-stage) | 1961.59 | 0.12203 | 5894.54ms | 94653 | 1280 | 4.03643e+06 | 46017.9 | 0.00335649 | 1.26136 | 2(Loss) | true |
| Glaze | 1864.92 | 0.136913 | 6236.75ms | 94653 | 1280 | 5.62143e+06 | 48403.2 | 0.54033 | 1.32671 | 3(Loss) | true |
| simdjson (ondemand) | 1343.13 | 0.0590031 | 8128.56ms | 94653 | 4890 | 7.68934e+06 | 67207.1 | 0.540949 | 1.84247 | 4(Loss) | true |
