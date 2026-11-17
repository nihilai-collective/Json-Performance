
----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2434.56 | 0.0726771 | 1194.74ms | 11812 | 4890 | 55298.1 | 4627.04 | 0.118063 | 2.13078 | 10.5002 | 1.84482 | 0.00293715 | 4.10833e-05 | 2.26798e-05 | 1(Win) | true |
| simdjson (ondemand) | 2091.43 | 0.0319498 | 1258.65ms | 11812 | 2560 | 7581.14 | 5386.16 | 0.0588006 | 2.47819 | 11.3337 | 1.89384 | 0.00353735 | 1.66674e-05 | 4.53062e-06 | 2(Loss) | true |
