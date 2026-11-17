
----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8430.96 | 0.315944 | 6244.35ms | 2090234 | 320 | 1.78569e+08 | 236438 | 0.128845 | 0.594696 | 3.18965 | 0.396912 | 0.00247093 | 0.0502538 | 3.5313e-06 | 1(Win) | true |
| simdjson (ondemand) | 7066.46 | 0.111379 | 7326.81ms | 2090234 | 80 | 7.89737e+06 | 282093 | 0.0171545 | 0.717452 | 3.66628 | 0.418404 | 0.00293722 | 0.0497695 | 2.3861e-06 | 2(Loss) | true |
