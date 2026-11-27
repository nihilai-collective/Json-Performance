
----
### Canada Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5171.29 | 0.264126 | 799.862ms | 4630 | 640 | 3255.13 | 853.852 | 0.342668 | 1.04231 | 5.12484 | 0.832182 | 0.000648286 | 1.11366e-05 | 1.34989e-06 | 1(Win) | true |
| simdjson (ondemand) | 4739.74 | 0.22673 | 809.735ms | 4630 | 320 | 1427.65 | 931.594 | 0.120234 | 1.13379 | 5.55421 | 0.812095 | 0.000647948 | 1.2149e-05 | 1.34989e-06 | 2(Loss) | true |
