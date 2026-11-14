
----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4587.14 | 0.0533834 | 1268.71ms | 25388 | 1280 | 10162.4 | 5278.21 | 0.0137672 | 1.13045 | 5.61005 | 0.888845 | 0.00147212 | 6.89302e-06 | 1.53862e-06 | 1(Win) | true |
| simdjson (ondemand) | 4017.96 | 0.0315552 | 1330.75ms | 25388 | 2560 | 9256.09 | 6025.91 | 0.125261 | 1.28907 | 5.90247 | 0.892666 | 0.00140802 | 1.14627e-05 | 1.20012e-06 | 2(Loss) | true |
