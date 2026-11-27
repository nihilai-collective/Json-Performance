
----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3923.03 | 0.07012 | 950.288ms | 9378 | 1280 | 3270.94 | 2279.76 | 0.150386 | 1.33673 | 5.79068 | 0.951376 | 0.00118829 | 3.40724e-05 | 1.44121e-05 | 1(Win) | true |
| simdjson (ondemand) | 3757.65 | 0.120022 | 959.829ms | 9378 | 640 | 5222.67 | 2380.1 | 0.0151625 | 1.3927 | 6.10471 | 0.908936 | 0.00131225 | 1.79942e-05 | 7.66421e-06 | 2(Loss) | true |
