
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1364.23 | 0.0368323 | 8520.76ms | 1922245 | 320 | 7.83886e+07 | 1.34376e+06 | 0.119378 | 3.7092 | 13.0167 | 0.630033 | 0.000723815 | 0.0584437 | 0.000135502 | 1(Win) | true |
| simdjson (reflection) | 1355.54 | 0.0712315 | 8575.81ms | 1922245 | 80 | 7.42385e+07 | 1.35238e+06 | 0.128031 | 3.74046 | 13.5126 | 1.1344 | 0.00879792 | 0.0507579 | 0.000401965 | 2(Loss) | true |
| Glaze | 990.218 | 0.205618 | 5496.92ms | 1833577 | 160 | 2.1095e+09 | 1.76591e+06 | 0.060436 | 5.10808 | 16.048 | 1.05269 | 0.00101463 | 0.0496013 | 0.000421993 | 3(Loss) | true |
