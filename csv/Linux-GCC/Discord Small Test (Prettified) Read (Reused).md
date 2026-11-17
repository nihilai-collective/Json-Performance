
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2492.8 | 0.0379351 | 1000.67ms | 6701 | 2560 | 2421.18 | 2563.61 | 0.0675469 | 2.09899 | 8.63758 | 1.53501 | 0.00185851 | 2.6407e-05 | 4.19713e-06 | 1(Win) | true |
| simdjson (ondemand) | 2300.56 | 0.0496718 | 1020.62ms | 6701 | 1280 | 2436.91 | 2777.83 | 0.0719098 | 2.27185 | 9.22937 | 1.52783 | 0.000536417 | 2.71648e-05 | 5.47959e-06 | 2(Loss) | true |
