
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2271.9 | 0.149274 | 8181.33ms | 360584 | 80 | 4.0841e+06 | 151362 | 0.309774 | 2.25707 | 8.10978 | 1.45249 | 0.00800618 | 9.92487e-05 | 4.78391e-06 | 1(Win) | true |
| simdjson (ondemand) | 1995.16 | 0.0529953 | 9226.89ms | 360584 | 2560 | 2.13586e+07 | 172357 | 0.15286 | 2.54734 | 8.62101 | 1.37215 | 0.0127421 | 0.00125551 | 1.37873e-05 | 2(Loss) | true |
