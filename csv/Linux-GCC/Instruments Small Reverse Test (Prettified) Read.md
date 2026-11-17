
----
### Instruments Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 849.305 | 0.0768325 | 1626.97ms | 7932 | 160 | 7492.87 | 8906.75 | 0.0213276 | 6.09337 | 24.357 | 4.87645 | 0.00529895 | 1.02433e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 413.22 | 0.0284235 | 2566.01ms | 7932 | 2560 | 69310.4 | 18306.3 | 0.0762783 | 12.4516 | 55.6612 | 11.2611 | 0.0303581 | 0.000118438 | 6.43655e-05 | 2(Loss) | true |
