
----
### Twitter Partial Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8391.46 | 0.15862 | 6070.53ms | 466906 | 320 | 2.26698e+06 | 53063 | 0.00477639 | 0.605365 | 3.03638 | 0.422091 | 0.000973811 | 1.11773e-05 | 7.20836e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 8352.73 | 0.0716765 | 6084.39ms | 466906 | 1280 | 1.86881e+06 | 53309 | 0.102013 | 0.604255 | 3.03329 | 0.421434 | 0.000939912 | 7.02765e-06 | 3.16579e-06 | 2(Loss) | true |
| simdjson (ondemand) | 6843.87 | 0.0386542 | 7279.35ms | 466906 | 2560 | 1.61916e+06 | 65062.1 | 0.0986706 | 0.737814 | 3.47604 | 0.378539 | 0.000714164 | 9.47561e-06 | 4.54956e-06 | 3(Loss) | true |
| Glaze | 3386.72 | 0.0575343 | 7120.76ms | 466906 | 1280 | 7.32429e+06 | 131477 | 0.0116282 | 1.50355 | 5.74476 | 0.997128 | 0.00171178 | 2.21287e-05 | 1.64129e-05 | 4(Loss) | true |
