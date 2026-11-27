
----
### Canada Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5692.75 | 0.116417 | 795.613ms | 4630 | 160 | 130.459 | 775.638 | 0.159801 | 0.95058 | 5.06242 | 0.835853 | 0.000647948 | 1.61987e-05 | 9.44924e-06 | 1(Win) | true |
| simdjson (ondemand) | 5119.88 | 0.133237 | 804.825ms | 4630 | 40 | 52.8147 | 862.425 | 0.0241509 | 1.05574 | 5.58877 | 0.820734 | 0.000647948 | 0 | 0 | 2(Loss) | true |
