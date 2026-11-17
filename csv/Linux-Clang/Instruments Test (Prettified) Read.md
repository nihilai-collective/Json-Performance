
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2816.16 | 0.0939177 | 6965.61ms | 183677 | 2560 | 8.73635e+06 | 62201 | 0.196665 | 1.79574 | 7.75 | 1.28315 | 0.00188951 | 2.06332e-05 | 1.25688e-05 | 1(Win) | true |
| Glaze | 2570.97 | 0.158832 | 7589.94ms | 183677 | 640 | 7.49496e+06 | 68133.1 | 0.135884 | 1.96895 | 9.22145 | 1.7258 | 0.00320376 | 3.42483e-05 | 1.98974e-05 | 2(Loss) | true |
| Jsonifier | 2167.52 | 0.181941 | 8848.02ms | 183677 | 640 | 1.38365e+07 | 80815 | 0.0615939 | 2.3315 | 8.42061 | 1.88919 | 0.00245034 | 2.28832e-05 | 1.6299e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1259.29 | 0.174871 | 7509ms | 183677 | 320 | 1.89343e+07 | 139101 | 0.0502283 | 3.98425 | 17.312 | 2.66702 | 0.00250327 | 2.23218e-05 | 1.24369e-05 | 4(Loss) | true |
