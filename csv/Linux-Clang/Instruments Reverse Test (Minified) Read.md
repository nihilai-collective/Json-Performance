
----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 630.247 | 0.0437915 | 8717.23ms | 108313 | 640 | 3.29686e+06 | 163897 | 0.106727 | 8.06347 | 38.0978 | 7.59829 | 0.0110979 | 2.08453e-05 | 5.84244e-06 | 1(Win) | true |
| simdjson (ondemand) | 241.524 | 0.17291 | 5502.12ms | 108313 | 320 | 1.74997e+08 | 427681 | 0.0828794 | 20.9796 | 100.159 | 18.1433 | 0.0704498 | 0.00024746 | 0.00015952 | 2(Loss) | true |
