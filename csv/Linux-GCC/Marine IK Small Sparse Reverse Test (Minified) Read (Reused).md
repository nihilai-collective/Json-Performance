
----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2503.16 | 0.128324 | 897.549ms | 4604 | 2560 | 12970.2 | 1754.07 | 0.0573781 | 2.09011 | 9.1477 | 1.7109 | 0.00108966 | 1.59508e-05 | 2.88472e-06 | 1(Win) | true |
| simdjson (ondemand) | 2251.23 | 0.0793351 | 922.524ms | 4604 | 30 | 71.8264 | 1950.37 | 0.0887933 | 2.33592 | 13.2921 | 2.35599 | 0.00126701 | 0.000166522 | 0.000137562 | 2(Loss) | true |
