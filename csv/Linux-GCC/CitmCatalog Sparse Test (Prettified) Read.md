
----
### CitmCatalog Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8752.44 | 0.116541 | 6869.43ms | 1151920 | 80 | 1.71172e+06 | 125514 | 0.0609067 | 0.584738 | 2.88336 | 0.336227 | 0.000606086 | 0.00788671 | 6.23958e-06 | 1(Win) | true |
| simdjson (ondemand) | 8046.65 | 0.0850656 | 7383.51ms | 1151920 | 2560 | 3.45273e+07 | 136524 | 0.0503683 | 0.633718 | 3.21555 | 0.347537 | 0.000889466 | 0.0100421 | 1.07236e-05 | 2(Loss) | true |
