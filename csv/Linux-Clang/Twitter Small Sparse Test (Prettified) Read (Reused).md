
----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6999.23 | 0.122885 | 763.007ms | 3770 | 640 | 255.014 | 513.678 | 0.130968 | 0.794047 | 3.19125 | 0.391777 | 0.000292192 | 1.03614e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6803.42 | 0.130918 | 765.95ms | 3770 | 1280 | 612.68 | 528.462 | 0.0745642 | 0.813985 | 3.26021 | 0.338727 | 0.00035664 | 3.12914e-05 | 1.07759e-05 | 2(Loss) | true |
