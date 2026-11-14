
----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4389.96 | 0.0375351 | 1272.85ms | 25388 | 2560 | 10971.1 | 5515.28 | 0.0148358 | 1.18078 | 5.69474 | 0.909879 | 0.00164037 | 6.20064e-06 | 8.924e-07 | 1(Win) | true |
| simdjson (ondemand) | 3968.41 | 0.0417345 | 1329.89ms | 25388 | 1280 | 8298.97 | 6101.15 | 0.00693981 | 1.30503 | 5.98925 | 0.914093 | 0.00130266 | 4.95436e-06 | 6.15448e-08 | 2(Loss) | true |
