
----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2222.57 | 0.0881423 | 902.286ms | 4390 | 1280 | 3528.56 | 1883.69 | 0.0335416 | 2.36348 | 10.6829 | 1.87039 | 0.00204086 | 3.11432e-05 | 8.54214e-06 | 1(Win) | true |
| simdjson (ondemand) | 1953.97 | 0.037052 | 930.6ms | 4390 | 2560 | 1613.46 | 2142.63 | 0.0408574 | 2.68379 | 11.5866 | 1.92847 | 0.0016998 | 2.35799e-05 | 1.95757e-06 | 2(Loss) | true |
