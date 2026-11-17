
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13146.5 | 0.0203894 | 6017.76ms | 728486 | 4890 | 567726 | 52845.8 | 0.171332 | 0.385022 | 1.84159 | 0.0690515 | 1.2088e-05 | 2.88269e-06 | 2.16097e-06 | 1(Win) | true |
| simdjson (stage-1) | 12917.3 | 0.116392 | 5999.65ms | 728486 | 80 | 313500 | 53783.7 | 0.125044 | 0.394332 | 1.96642 | 0.0748814 | 0.000375573 | 1.09817e-06 | 6.69196e-07 | 2(Loss) | true |
