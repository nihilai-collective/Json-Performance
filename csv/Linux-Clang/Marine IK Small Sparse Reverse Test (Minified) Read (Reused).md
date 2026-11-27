
----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2621.69 | 0.0814482 | 900.866ms | 4604 | 2560 | 4763.35 | 1674.77 | 0.380942 | 2.01439 | 9.07754 | 1.72871 | 0.00106853 | 2.70655e-05 | 8.82385e-06 | 1(Win) | true |
| simdjson (ondemand) | 2273.53 | 0.187953 | 911.825ms | 4604 | 2560 | 33729.5 | 1931.24 | 0.0397612 | 2.31587 | 13.2291 | 2.33341 | 0.00126283 | 4.49677e-05 | 2.12112e-05 | 2(Loss) | true |
