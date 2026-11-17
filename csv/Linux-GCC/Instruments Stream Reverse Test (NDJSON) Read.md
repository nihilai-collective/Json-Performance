
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 842.614 | 0.106403 | 7315.91ms | 4197496 | 80 | 2.0442e+09 | 4.75074e+06 | 0.242851 | 6.00953 | 30.3192 | 5.40528 | 0.0105933 | 0.0795177 | 0.00056093 | 1(Win) | true |
| Jsonifier (generic) | 791.737 | 0.103602 | 7718.89ms | 4197496 | 30 | 8.23141e+08 | 5.05603e+06 | 0.572515 | 6.3935 | 27.699 | 5.68614 | 0.000709629 | 0.0793489 | 0.00084359 | 2(Loss) | true |
