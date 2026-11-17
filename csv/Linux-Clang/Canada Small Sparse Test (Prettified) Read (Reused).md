
----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12908.2 | 0.0659777 | 800.848ms | 11579 | 2560 | 815.535 | 855.469 | 0.00620966 | 0.417676 | 2.08982 | 0.207704 | 0.000173367 | 3.64345e-06 | 3.03621e-07 | 1(Win) | true |
| simdjson (ondemand) | 11242.4 | 0.0708387 | 813.208ms | 11579 | 160 | 77.4619 | 982.231 | 0.0883684 | 0.477289 | 2.35331 | 0.228344 | 0.000172726 | 7.01701e-06 | 4.85793e-06 | 2(Loss) | true |
