
----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 956.494 | 0.051551 | 9776.9ms | 360584 | 640 | 2.19838e+07 | 359521 | 0.00874394 | 5.32378 | 20.6554 | 3.83491 | 0.0138616 | 0.00130421 | 1.7034e-05 | 1(Win) | true |
| simdjson (ondemand) | 411.173 | 0.364119 | 5431.71ms | 360584 | 30 | 2.78209e+08 | 836338 | 0.0960013 | 12.3076 | 51.8408 | 8.95972 | 0.0502329 | 7.4971e-05 | 1.06309e-05 | 2(Loss) | true |
