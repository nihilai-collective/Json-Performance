
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1699.84 | 0.0337299 | 5308.2ms | 728486 | 640 | 1.21629e+07 | 408709 | 0.0894229 | 2.97115 | 12.498 | 2.27534 | 0.0154185 | 0.0706515 | 2.80183e-05 | 1(Win) | true |
| Glaze | 1546.96 | 0.0628583 | 5812.45ms | 728486 | 640 | 5.10023e+07 | 449099 | 0.00641347 | 3.26447 | 14.8121 | 2.94434 | 0.0105721 | 0.032284 | 0.000102132 | 2(Loss) | true |
| Jsonifier | 1391.72 | 0.0357516 | 6442.52ms | 728486 | 640 | 2.0385e+07 | 499194 | 0.117502 | 3.62921 | 13.9451 | 2.85952 | 0.0128095 | 0.038391 | 3.50213e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1254.05 | 0.0851134 | 7148ms | 728486 | 640 | 1.42294e+08 | 553994 | 0.147036 | 4.00202 | 16.5315 | 2.85935 | 0.00716196 | 0.0749455 | 0.000201677 | 4(Loss) | true |
