
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1670.71 | 0.0513246 | 7093.71ms | 108313 | 640 | 644452 | 61827.3 | 0.0213023 | 3.04233 | 14.0168 | 2.64686 | 0.00348241 | 1.87535e-05 | 1.38343e-05 | 1(Win) | true |
| simdjson (ondemand) | 1553.72 | 0.0532238 | 7599.22ms | 108313 | 1280 | 1.60264e+06 | 66482.5 | 0.0281662 | 3.27236 | 15.7286 | 2.28477 | 0.00597362 | 1.20239e-05 | 7.76828e-06 | 2(Loss) | true |
