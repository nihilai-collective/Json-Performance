
----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 947.557 | 1.29152 | 6540.11ms | 4197495 | 30 | 8.93083e+10 | 4.22459e+06 | 0.431996 | 5.34621 | 27.2051 | 5.60614 | 0.00102148 | 0.0846677 | 0.00361267 | 1(Win) | true |
| simdjson (ondemand) | 639.714 | 0.551555 | 9583.8ms | 4197495 | 80 | 9.52962e+10 | 6.25755e+06 | 0.0489393 | 7.93193 | 39.2688 | 6.37123 | 0.00872534 | 0.103639 | 0.00778893 | 2(Loss) | true |
