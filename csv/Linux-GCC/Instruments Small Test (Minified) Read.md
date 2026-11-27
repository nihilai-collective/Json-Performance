
----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1623.22 | 0.161439 | 999.604ms | 4669 | 80 | 1568.93 | 2743.14 | 0.0770697 | 3.21948 | 12.9218 | 2.61362 | 0.00179642 | 2.67723e-05 | 1.07089e-05 | 1(Win) | true |
| simdjson (ondemand) | 1492.37 | 0.299848 | 1026.34ms | 4669 | 640 | 51224.3 | 2983.65 | 0.00780356 | 3.49698 | 15.0621 | 2.43393 | 0.00140086 | 0.000134531 | 6.25803e-05 | 2(Loss) | true |
