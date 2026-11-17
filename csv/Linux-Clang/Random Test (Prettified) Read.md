
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1686.69 | 0.067283 | 5348.11ms | 728486 | 320 | 2.45773e+07 | 411895 | 0.0830125 | 2.98439 | 12.4962 | 2.27471 | 0.0154814 | 0.071427 | 0.000284215 | 1(Win) | true |
| Glaze | 1557.96 | 0.0995252 | 5778.45ms | 728486 | 640 | 1.2606e+08 | 445928 | 0.334402 | 3.22885 | 14.81 | 2.94403 | 0.010732 | 0.0294245 | 0.000306638 | 2(Loss) | true |
| Jsonifier | 1415.32 | 0.226216 | 6356.69ms | 728486 | 80 | 9.8644e+07 | 490870 | 0.0953299 | 3.56569 | 13.9447 | 2.85958 | 0.0128893 | 0.0387485 | 0.000168329 | 3(Loss) | true |
| simdjson (ondemand) | 1253.87 | 0.12471 | 7151.23ms | 728486 | 320 | 1.52787e+08 | 554074 | 0.0865338 | 3.97686 | 16.5298 | 2.85889 | 0.00728439 | 0.0727059 | 0.000860977 | 4(Loss) | true |
