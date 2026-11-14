
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2503.73 | 0.176502 | 3818.68ms | 65103 | 1280 | 2.45211e+06 | 24797.9 | 0.0139011 | 2.0148 | 7.28426 | 1.14738 | 0.00598235 | 4.57328e-05 | 2.75045e-05 | 1(Win) | true |
| Jsonifier | 1964.94 | 0.186954 | 4520.42ms | 65103 | 640 | 2.23335e+06 | 31597.5 | 0.0134486 | 2.57586 | 7.85405 | 1.42919 | 0.0078239 | 4.91049e-05 | 2.80565e-05 | 2(Loss) | true |
| Glaze | 1917.3 | 0.0525116 | 4641.4ms | 65103 | 4890 | 1.41398e+06 | 32382.6 | 0.0619475 | 2.63955 | 9.08224 | 1.68838 | 0.0179217 | 3.51339e-05 | 1.95537e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1365.46 | 0.0666027 | 5860.79ms | 65103 | 4890 | 4.48475e+06 | 45469.8 | 0.0718436 | 3.70472 | 11.2426 | 1.91551 | 0.0095141 | 4.31313e-05 | 2.19096e-05 | 4(Loss) | true |
