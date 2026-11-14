
----
### Canada Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 12889.9 | 0.0290108 | 799.051ms | 11579 | 1280 | 79.0624 | 856.684 | 0.0166914 | 0.420178 | 2.08982 | 0.207704 | 0.000172726 | 9.10862e-06 | 1.21448e-06 | 1(Win) | true |
| simdjson (ondemand) | 11243.6 | 0.0714508 | 809.272ms | 11579 | 160 | 78.7893 | 982.125 | 0.129989 | 0.477215 | 2.35219 | 0.227913 | 0.000172726 | 4.31816e-06 | 0 | 2(Loss) | true |
