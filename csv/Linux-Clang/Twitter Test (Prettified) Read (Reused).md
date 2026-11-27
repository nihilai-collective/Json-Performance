
----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2815.43 | 0.042123 | 7400.79ms | 360584 | 1280 | 3.38824e+06 | 122141 | 0.138409 | 1.80789 | 7.05567 | 1.16304 | 0.00382446 | 3.18624e-05 | 1.02265e-05 | 1(Win) | true |
| simdjson (ondemand) | 2473 | 0.0656853 | 8267.13ms | 360584 | 1280 | 1.06785e+07 | 139054 | 0.0237037 | 2.04537 | 7.54354 | 1.12266 | 0.00751625 | 0.000432837 | 7.74135e-06 | 2(Loss) | true |
