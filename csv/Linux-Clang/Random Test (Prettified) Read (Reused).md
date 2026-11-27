
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3267.79 | 0.125401 | 7351.24ms | 728486 | 320 | 2.27449e+07 | 212602 | 0.0972318 | 1.54241 | 8.18403 | 1.55517 | 0.00341228 | 0.00889601 | 2.13971e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2216.99 | 0.0606061 | 9970.6ms | 728486 | 1280 | 4.61699e+07 | 313370 | 0.0741411 | 2.28262 | 10.6703 | 1.70079 | 0.0108824 | 0.0288706 | 5.51486e-05 | 2(Loss) | true |
| Glaze | 1708.64 | 0.17412 | 6142.79ms | 728486 | 160 | 8.01968e+07 | 406602 | 0.0156243 | 2.96662 | 12.3013 | 2.37938 | 0.00877032 | 0.011865 | 2.19462e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1562.44 | 0.1507 | 6551.11ms | 728486 | 320 | 1.43685e+08 | 444651 | 0.0623914 | 3.21783 | 14.1064 | 2.25544 | 0.00259473 | 0.0319342 | 0.000133526 | 4(Loss) | true |
