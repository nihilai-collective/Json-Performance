
----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12210.8 | 0.0472857 | 804.598ms | 11579 | 4890 | 894.174 | 904.33 | 0.182723 | 0.439573 | 2.11262 | 0.205631 | 0.000173009 | 1.03495e-05 | 8.30076e-07 | 1(Win) | true |
| simdjson (ondemand) | 11094.8 | 0.0526308 | 811.681ms | 11579 | 320 | 87.8081 | 995.297 | 0.139915 | 0.482569 | 2.43665 | 0.22869 | 0.000172726 | 1.16051e-05 | 0 | 2(Loss) | true |
