
----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8715.56 | 0.0288387 | 1320.07ms | 53331 | 2560 | 7250.35 | 5835.59 | 0.0330584 | 0.594898 | 2.82537 | 0.382536 | 0.000736497 | 3.5231e-06 | 6.59209e-07 | 1(Win) | true |
| simdjson (ondemand) | 7206.49 | 0.0946413 | 1439.19ms | 53331 | 320 | 14276.6 | 7057.59 | 0.0437281 | 0.71838 | 3.18515 | 0.380042 | 0.000838806 | 4.8049e-06 | 1.05473e-06 | 2(Loss) | true |
