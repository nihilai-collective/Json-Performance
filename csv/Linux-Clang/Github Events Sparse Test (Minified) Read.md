
----
### Github Events Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8240.96 | 0.0535415 | 1349.44ms | 53331 | 1280 | 13976.4 | 6171.66 | 0.0209672 | 0.627457 | 2.88718 | 0.418162 | 0.000664336 | 4.26288e-06 | 1.09868e-06 | 1(Win) | true |
| simdjson (ondemand) | 6744.28 | 0.0318197 | 1486.35ms | 53331 | 4890 | 28157.1 | 7541.27 | 0.144861 | 0.759252 | 3.34571 | 0.415875 | 0.000861978 | 3.44724e-06 | 7.13221e-07 | 2(Loss) | true |
