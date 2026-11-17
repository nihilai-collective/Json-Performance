
----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2621.6 | 0.0655341 | 887.907ms | 4604 | 1280 | 1542 | 1674.83 | 0.0156291 | 2.00926 | 9.43419 | 1.6755 | 0.000946018 | 3.2241e-05 | 1.23873e-05 | 1(Win) | true |
| simdjson (ondemand) | 2054.12 | 0.0563287 | 927.915ms | 4604 | 4890 | 7089.05 | 2137.52 | 0.305212 | 2.55195 | 13.273 | 2.35491 | 0.00127075 | 2.35414e-05 | 5.7743e-06 | 2(Loss) | true |
