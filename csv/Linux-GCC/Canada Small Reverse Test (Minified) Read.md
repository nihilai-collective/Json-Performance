
----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 714.227 | 0.094803 | 1341.15ms | 4630 | 4890 | 167974 | 6182.22 | 0.00720883 | 7.23737 | 35.6914 | 6.70605 | 0.00338302 | 8.88665e-05 | 4.71275e-05 | 1(Win) | true |
| Jsonifier (generic) | 661.689 | 0.0571575 | 1387.83ms | 4630 | 160 | 2327.67 | 6673.09 | 0.229966 | 7.83207 | 34.6821 | 7.10518 | 0.00976647 | 3.7797e-05 | 8.09935e-06 | 2(Loss) | true |
