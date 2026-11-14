
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2834.91 | 0.0266276 | 7350.87ms | 360584 | 2560 | 2.67079e+06 | 121302 | 0.339309 | 1.79657 | 7.04821 | 1.20876 | 0.00368194 | 1.26737e-05 | 3.04627e-06 | 1(Win) | true |
| simdjson (ondemand) | 2385.71 | 0.0513427 | 8557.19ms | 360584 | 2560 | 1.40208e+07 | 144141 | 0.182624 | 2.12988 | 7.56047 | 1.12743 | 0.00970522 | 5.06329e-05 | 6.40454e-06 | 2(Loss) | true |
