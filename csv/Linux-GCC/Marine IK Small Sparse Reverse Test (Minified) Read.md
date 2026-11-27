
----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2414.75 | 0.079607 | 900.884ms | 4604 | 4890 | 10245.6 | 1818.29 | 0.28037 | 2.17786 | 9.22719 | 1.73002 | 0.00109423 | 3.50011e-05 | 1.95882e-05 | 1(Win) | true |
| simdjson (ondemand) | 2229.17 | 0.152394 | 914.803ms | 4604 | 30 | 270.299 | 1969.67 | 0.00169236 | 2.35817 | 13.3732 | 2.37467 | 0.000984651 | 2.17202e-05 | 0 | 2(Loss) | true |
