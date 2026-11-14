
----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 685.702 | 0.0916815 | 1396.82ms | 4857 | 4890 | 187559 | 6755.12 | 0.0611869 | 7.54487 | 31.0601 | 6.21824 | 0.00827562 | 5.93666e-05 | 1.46522e-05 | 1(Win) | true |
| simdjson (ondemand) | 238.881 | 0.0444681 | 2664.59ms | 4857 | 320 | 23791.4 | 19390.4 | 0.0135878 | 21.5976 | 107.356 | 22.5893 | 0.0483767 | 9.39366e-05 | 3.79607e-05 | 2(Loss) | true |
