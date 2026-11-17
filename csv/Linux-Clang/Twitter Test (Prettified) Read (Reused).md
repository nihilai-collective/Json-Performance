
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2702.31 | 0.102224 | 7601.57ms | 360584 | 160 | 2.70749e+06 | 127254 | 0.0654805 | 1.87446 | 7.05969 | 1.2107 | 0.0057908 | 1.07465e-05 | 1.7853e-06 | 1(Win) | true |
| simdjson (ondemand) | 2361.69 | 0.0427085 | 8697.43ms | 360584 | 2560 | 9.90003e+06 | 145607 | 0.243628 | 2.16848 | 7.57831 | 1.1329 | 0.0106899 | 0.000186147 | 1.47233e-05 | 2(Loss) | true |
