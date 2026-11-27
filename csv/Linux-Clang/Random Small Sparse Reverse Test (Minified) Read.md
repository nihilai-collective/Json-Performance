
----
### Random Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1935.16 | 0.102671 | 966.694ms | 4926 | 80 | 496.977 | 2427.6 | 0.0329652 | 2.70785 | 11.8084 | 2.22452 | 0.00347391 | 2.03004e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1507.51 | 0.0385608 | 1033.37ms | 4926 | 4890 | 7061.06 | 3116.26 | 0.00029733 | 3.44364 | 14.5828 | 2.43443 | 0.00722023 | 2.21271e-05 | 2.36631e-06 | 2(Loss) | true |
