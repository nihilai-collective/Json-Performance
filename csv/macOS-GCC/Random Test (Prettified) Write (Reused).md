
----
### Random Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14781.3 | 0.113136 | 5564.22ms | 837491 | 2560 | 9.56689e+06 | 54033.9 | 0.337349 | 1(Win) | true |
| Glaze | 2680.43 | 0.23324 | 7552.69ms | 837491 | 640 | 3.09127e+08 | 297972 | 0.123617 | 2(Loss) | true |
| simdjson (reflection) | 319.291 | 0.516395 | 7997.55ms | 837491 | 30 | 5.0058e+09 | 2.50146e+06 | 0.434781 | 3(Loss) | true |
