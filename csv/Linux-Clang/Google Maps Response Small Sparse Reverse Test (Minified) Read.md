
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1758.39 | 0.0522507 | 967.435ms | 4390 | 320 | 495.26 | 2380.95 | 0.078033 | 2.97946 | 14.0765 | 2.64374 | 0.00447893 | 1.99317e-05 | 4.27107e-06 | 1(Win) | true |
| simdjson (ondemand) | 1596.07 | 0.0440254 | 978.452ms | 4390 | 1280 | 1707.03 | 2623.09 | 0.0437032 | 3.27507 | 14.738 | 2.43212 | 0.00324868 | 2.01096e-05 | 3.38126e-06 | 2(Loss) | true |
