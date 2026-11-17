
----
### Canada Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5376.38 | 0.101834 | 795.745ms | 4630 | 2560 | 1790.63 | 821.279 | 0.00623036 | 1.00417 | 5.09482 | 0.800864 | 0.00064837 | 1.4427e-05 | 5.65267e-06 | 1(Win) | true |
| simdjson (ondemand) | 4222.26 | 0.118653 | 819.501ms | 4630 | 1280 | 1970.78 | 1045.77 | 0.517688 | 1.26658 | 5.58575 | 0.819655 | 0.000650985 | 1.41739e-05 | 3.03726e-06 | 2(Loss) | true |
