
----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6419.35 | 0.0614777 | 833.182ms | 7932 | 320 | 167.945 | 1178.4 | 0.0618277 | 0.830548 | 3.65721 | 0.483737 | 0.000562201 | 2.00927e-05 | 1.5759e-06 | 1(Win) | true |
| simdjson (ondemand) | 6230.83 | 0.0674947 | 836.522ms | 7932 | 1280 | 859.454 | 1214.05 | 0.0891748 | 0.853589 | 3.81934 | 0.433813 | 0.000892843 | 5.02317e-06 | 1.37891e-06 | 2(Loss) | true |
