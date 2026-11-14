
----
### Marine IK Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2495.28 | 0.186105 | 893.641ms | 4604 | 1280 | 13726.5 | 1759.61 | 0.516529 | 2.12794 | 9.24066 | 1.66942 | 0.00110621 | 4.24224e-05 | 8.14509e-06 | 1(Win) | true |
| simdjson (ondemand) | 1822.99 | 0.0205547 | 955.642ms | 4604 | 640 | 156.857 | 2408.52 | 0.0582228 | 2.87204 | 13.3677 | 2.37294 | 0.00149802 | 1.32358e-05 | 3.39379e-07 | 2(Loss) | true |
