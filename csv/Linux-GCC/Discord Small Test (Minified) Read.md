
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2024.83 | 0.189117 | 959.938ms | 4857 | 40 | 748.656 | 2287.6 | 0.0510256 | 2.58966 | 9.75685 | 1.73687 | 0.000488985 | 4.11777e-05 | 0 | 1(Win) | true |
| Glaze | 1807.97 | 0.0749886 | 982.683ms | 4857 | 4890 | 18049 | 2561.99 | 0.00676957 | 2.87942 | 11.4674 | 2.26539 | 0.000372031 | 8.04607e-05 | 3.49884e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1682.22 | 0.0407938 | 1008.21ms | 4857 | 4890 | 6169.78 | 2753.51 | 0.231982 | 3.09882 | 12.0465 | 1.97447 | 0.00104506 | 6.05034e-05 | 2.56413e-05 | 3(Loss) | true |
| simdjson (reflection) | 1509.69 | 0.0981056 | 1036.88ms | 4857 | 1280 | 11597.4 | 3068.18 | 0.0193227 | 3.41835 | 12.9135 | 2.19807 | 0.00114831 | 3.77998e-05 | 1.33506e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1258.3 | 0.0549246 | 1098.83ms | 4857 | 2560 | 10465 | 3681.15 | 0.0516728 | 4.12653 | 14.3801 | 2.73317 | 0.00197653 | 0.000124981 | 5.90321e-05 | 5(Loss) | true |
