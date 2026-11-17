
----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8711.05 | 0.0202482 | 1330.72ms | 53331 | 4890 | 6834.37 | 5838.61 | 0.142183 | 0.59511 | 2.83355 | 0.384186 | 0.000699613 | 4.82767e-06 | 1.56832e-06 | 1(Win) | true |
| simdjson (ondemand) | 7376.76 | 0.023315 | 1425.45ms | 53331 | 2560 | 6615.14 | 6894.68 | 0.0344293 | 0.702216 | 3.1867 | 0.380473 | 0.000934509 | 2.8346e-06 | 2.19736e-07 | 2(Loss) | true |
