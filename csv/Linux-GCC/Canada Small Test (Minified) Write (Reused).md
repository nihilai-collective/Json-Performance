
----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1979.52 | 0.166403 | 952.271ms | 4630 | 640 | 8817.55 | 2230.6 | 0.0138014 | 2.58307 | 7.70756 | 0.385314 | 0.00024433 | 3.03726e-05 | 6.41199e-06 | 1(Win) | true |
| Glaze | 1658.58 | 0.0448734 | 994.817ms | 4630 | 4890 | 6978.7 | 2662.22 | 0.207756 | 3.08756 | 9.48315 | 0.60432 | 0.000221945 | 3.63946e-05 | 1.31621e-05 | 2(Loss) | true |
| simdjson (reflection) | 1071.84 | 0.0279252 | 1137.05ms | 4630 | 30 | 39.7023 | 4119.57 | 0.0372069 | 4.76487 | 15.2991 | 1.42743 | 0.000431965 | 0 | 0 | 3(Loss) | true |
