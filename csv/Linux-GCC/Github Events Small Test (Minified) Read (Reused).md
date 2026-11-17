
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1409.35 | 0.151598 | 845.763ms | 1691 | 80 | 240.728 | 1144.26 | 0.0600463 | 3.78321 | 13.1821 | 2.46008 | 0.0019589 | 2.21762e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1396.09 | 0.0716658 | 847.36ms | 1691 | 2560 | 1754.38 | 1155.13 | 0.0565734 | 3.78655 | 13.6777 | 2.49084 | 0.000594831 | 0.000142066 | 3.99634e-05 | 2(Loss) | true |
