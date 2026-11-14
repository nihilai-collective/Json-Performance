
----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2968.28 | 0.0730924 | 864.236ms | 4604 | 160 | 187.036 | 1479.21 | 0.0312764 | 1.78357 | 9.34839 | 1.65617 | 0.000897318 | 2.17202e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2069.06 | 0.0404905 | 928.345ms | 4604 | 2560 | 1890.04 | 2122.08 | 0.0560827 | 2.53596 | 13.1755 | 2.33145 | 0.00114676 | 5.41309e-05 | 2.40111e-05 | 2(Loss) | true |
