
----
### Discord Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6032.08 | 0.101937 | 830.878ms | 6701 | 320 | 373.218 | 1059.43 | 0.109849 | 0.86828 | 3.88718 | 0.529622 | 0.000447694 | 1.11924e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 5313.96 | 0.160746 | 868.119ms | 6701 | 30 | 112.11 | 1202.6 | 0.0138608 | 0.987703 | 4.33353 | 0.529473 | 0.000179078 | 0 | 0 | 2(Loss) | true |
