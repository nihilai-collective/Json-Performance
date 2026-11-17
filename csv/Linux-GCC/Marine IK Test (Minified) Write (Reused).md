
----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1297.45 | 0.0620884 | 8542.71ms | 1834197 | 80 | 5.6056e+07 | 1.3482e+06 | 0.0595456 | 3.88806 | 13.1199 | 0.79904 | 0.00174471 | 0.0616282 | 9.69702e-05 | 1(Win) | true |
| Glaze | 1002.42 | 0.269008 | 5432.11ms | 1833577 | 160 | 3.52327e+09 | 1.74441e+06 | 0.101865 | 5.02356 | 16.0427 | 1.0527 | 0.000994112 | 0.0495293 | 0.000164852 | 2(Loss) | true |
| simdjson (reflection) | 890.745 | 0.0446625 | 6416.66ms | 1922245 | 80 | 6.75907e+07 | 2.05805e+06 | 0.0106716 | 5.67667 | 18.1619 | 2.01848 | 0.0245876 | 0.0519765 | 0.000198837 | 3(Loss) | true |
