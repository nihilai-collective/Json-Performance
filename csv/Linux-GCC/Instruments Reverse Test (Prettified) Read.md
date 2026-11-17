
----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 894.393 | 0.108527 | 5200.88ms | 183677 | 160 | 7.22852e+06 | 195851 | 0.246488 | 5.71994 | 23.9695 | 4.81131 | 0.00649921 | 9.83384e-06 | 5.37629e-06 | 1(Win) | true |
| simdjson (ondemand) | 433.437 | 0.0803951 | 5233.76ms | 183677 | 160 | 1.68903e+07 | 404137 | 0.216236 | 11.7663 | 53.3754 | 10.778 | 0.045039 | 8.81643e-05 | 6.4039e-05 | 2(Loss) | true |
