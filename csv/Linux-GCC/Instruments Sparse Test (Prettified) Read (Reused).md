
----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6985.11 | 0.0531364 | 3280.66ms | 183677 | 320 | 56819.6 | 25077.4 | 0.0152256 | 0.738027 | 3.80574 | 0.482091 | 0.000567777 | 3.21556e-06 | 2.50099e-06 | 1(Win) | true |
| simdjson (ondemand) | 6724.51 | 0.0260782 | 3354.04ms | 183677 | 2560 | 118137 | 26049.2 | 0.115384 | 0.758284 | 3.99167 | 0.454276 | 0.000774823 | 2.36489e-06 | 1.21434e-06 | 2(Loss) | true |
