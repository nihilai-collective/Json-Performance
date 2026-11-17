
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Glaze | 1917.4 | 0.07643 | 6136.91ms | 466906 | 640 | 2.01624e+07 | 232230 | 0.0241966 | 2.63789 | 10.0403 | 1.7982 | 0.0103339 | 0.00755563 | 2.24316e-05 | 1(Win) | true |
| Jsonifier | 1889.77 | 0.0687495 | 6208.5ms | 466906 | 1280 | 3.35885e+07 | 235625 | 0.0735319 | 2.67035 | 8.29876 | 1.47148 | 0.0108222 | 0.00929959 | 3.53993e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1756.2 | 0.199195 | 6692.01ms | 466906 | 160 | 4.08123e+07 | 253546 | 0.16404 | 2.87491 | 9.22493 | 1.5301 | 0.0151684 | 0.0256547 | 6.99418e-05 | 3(Loss) | true |
| simdjson (ondemand) | 933.973 | 0.0870075 | 6161.81ms | 466906 | 640 | 1.10124e+08 | 476755 | 0.107543 | 5.31813 | 18.181 | 3.17146 | 0.0124896 | 0.0284879 | 7.95965e-05 | 4(Loss) | true |
