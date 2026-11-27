
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2594.7 | 0.172859 | 5339.62ms | 466906 | 640 | 5.63179e+07 | 171610 | 0.0308791 | 1.955 | 5.84017 | 1.05907 | 0.00817967 | 0.00265717 | 7.00589e-05 | 1(Win) | true |
| Glaze | 2343.32 | 0.118064 | 5780.94ms | 466906 | 640 | 3.22112e+07 | 190019 | 0.0958212 | 2.16177 | 8.57405 | 1.45943 | 0.0092106 | 0.00232992 | 2.37099e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2012.75 | 0.114382 | 6654.96ms | 466906 | 1280 | 8.19606e+07 | 221228 | 0.169043 | 2.50735 | 8.25312 | 1.24285 | 0.0165007 | 0.00772285 | 5.50348e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1043.33 | 0.174068 | 5876.87ms | 466906 | 160 | 8.83028e+07 | 426784 | 0.102181 | 4.82193 | 17.284 | 2.84229 | 0.00942457 | 0.0110402 | 4.79352e-05 | 4(Loss) | true |
