
----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3312.16 | 0.100108 | 861.043ms | 4857 | 160 | 313.597 | 1398.48 | 0.0576186 | 1.60118 | 6.96644 | 1.19518 | 0.00138717 | 1.2868e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2255.64 | 0.0519449 | 925.675ms | 4857 | 1280 | 1456.44 | 2053.52 | 0.086893 | 2.32808 | 10.1069 | 1.5279 | 0.00318033 | 1.44765e-05 | 3.37786e-06 | 2(Loss) | true |
