
----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4863.04 | 0.0368566 | 1250.74ms | 25388 | 4890 | 16465.7 | 4978.76 | 0.209805 | 1.05752 | 5.27395 | 0.844494 | 0.00117907 | 1.49419e-05 | 6.09759e-06 | 1(Win) | true |
| simdjson (ondemand) | 3974.8 | 0.037392 | 1358.64ms | 25388 | 4890 | 25368.4 | 6091.34 | 0.187522 | 1.28537 | 5.77497 | 0.878289 | 0.00190657 | 1.94608e-05 | 9.64983e-06 | 2(Loss) | true |
