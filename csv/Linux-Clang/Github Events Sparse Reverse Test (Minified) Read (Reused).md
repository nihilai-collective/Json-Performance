
----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6150.74 | 0.0261078 | 1588.02ms | 53331 | 2560 | 11931.2 | 8268.98 | 0.00717049 | 0.841185 | 4.19786 | 0.674261 | 0.00154283 | 3.32534e-06 | 6.59209e-07 | 1(Win) | true |
| simdjson (ondemand) | 4254.65 | 0.022595 | 1958.04ms | 53331 | 2560 | 18676.5 | 11954.1 | 0.00189204 | 1.21387 | 5.73871 | 0.911403 | 0.00219147 | 4.18964e-06 | 7.98375e-07 | 2(Loss) | true |
