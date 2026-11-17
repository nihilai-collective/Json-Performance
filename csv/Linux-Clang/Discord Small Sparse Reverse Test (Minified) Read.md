
----
### Discord Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3043.36 | 0.117405 | 875.838ms | 4857 | 80 | 255.443 | 1522 | 0.0542344 | 1.73613 | 7.53675 | 1.3218 | 0.000509574 | 7.72082e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2186.49 | 0.0528314 | 949.54ms | 4857 | 2560 | 3206.76 | 2118.46 | 0.165339 | 2.39797 | 10.6848 | 1.65905 | 0.00143438 | 2.19561e-05 | 4.18211e-06 | 2(Loss) | true |
