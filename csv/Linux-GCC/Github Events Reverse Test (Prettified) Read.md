
----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1073.7 | 0.0233954 | 6541.66ms | 65103 | 4890 | 894960 | 57825.1 | 0.0259867 | 4.79417 | 16.9372 | 3.38629 | 0.0137918 | 6.56157e-05 | 2.95646e-05 | 1(Win) | true |
| simdjson (ondemand) | 598.08 | 0.0809325 | 5701.31ms | 65103 | 640 | 4.51762e+06 | 103811 | 0.118038 | 8.57998 | 30.2261 | 6.07172 | 0.0555306 | 0.000105602 | 6.49692e-05 | 2(Loss) | true |
