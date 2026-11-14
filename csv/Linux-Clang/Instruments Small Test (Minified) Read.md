
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1438.88 | 0.039891 | 1027.42ms | 4669 | 2560 | 3901.14 | 3094.57 | 0.0107031 | 3.62487 | 14.7356 | 2.98802 | 0.00297725 | 5.25407e-05 | 1.42228e-05 | 1(Win) | true |
| simdjson (ondemand) | 1433.44 | 0.0339252 | 1029.64ms | 4669 | 4890 | 5430.5 | 3106.3 | 0.0446069 | 3.63728 | 16.4716 | 2.48554 | 0.00160564 | 3.07909e-05 | 2.80316e-06 | 2(Loss) | true |
