
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1728.44 | 0.0611895 | 958.911ms | 4390 | 640 | 1405.9 | 2422.2 | 0.135475 | 3.02788 | 13.7998 | 2.59066 | 0.00363255 | 2.70501e-05 | 7.11845e-06 | 1(Win) | true |
| simdjson (ondemand) | 1589.64 | 0.043954 | 977.647ms | 4390 | 2560 | 3430.59 | 2633.7 | 0.0950732 | 3.28778 | 14.1419 | 2.45581 | 0.00404844 | 2.80289e-05 | 4.00413e-06 | 2(Loss) | true |
