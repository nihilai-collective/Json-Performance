
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1770.34 | 0.0842651 | 846.443ms | 2158 | 160 | 153.535 | 1162.51 | 0.288463 | 3.00836 | 10.8832 | 2.01483 | 0.000474977 | 9.26784e-05 | 5.7924e-06 | 1(Win) | true |
| simdjson (ondemand) | 1759.76 | 0.0853692 | 847.435ms | 2158 | 160 | 159.484 | 1169.49 | 0.1851 | 3.02519 | 10.9411 | 1.94532 | 0.000463392 | 7.53012e-05 | 5.7924e-06 | 2(Loss) | true |
