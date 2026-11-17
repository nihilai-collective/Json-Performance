
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2191.7 | 0.021771 | 6088.46ms | 94653 | 2560 | 205827 | 41186.3 | 0.060645 | 2.31465 | 11.1468 | 2.08898 | 0.00608877 | 6.5783e-06 | 3.1282e-06 | 1(Win) | true |
| simdjson (ondemand) | 1647.19 | 0.0788334 | 7485.48ms | 94653 | 320 | 597244 | 54801.3 | 0.0224169 | 3.08468 | 12.7599 | 2.23621 | 0.00993986 | 5.77768e-06 | 2.146e-06 | 2(Loss) | true |
