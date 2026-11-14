
----
### Google Maps Response Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2625.37 | 0.112288 | 926.164ms | 25388 | 2560 | 274526 | 9222.27 | 0.076184 | 1.155 | 1(Win) | true |
| simdjson (ondemand) | 2392.63 | 0.0899184 | 1009.64ms | 25388 | 4890 | 404867 | 10119.4 | 0.243457 | 1.26749 | 2(Loss) | true |
