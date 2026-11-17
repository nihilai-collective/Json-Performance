
----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5113.83 | 0.0787693 | 741.238ms | 1691 | 640 | 39.4901 | 315.353 | 0.136939 | 1.14062 | 4.22413 | 0.656416 | 0.00061539 | 1.20121e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4553.4 | 0.0403511 | 751.062ms | 1691 | 2560 | 52.2839 | 354.167 | 0.13098 | 1.25824 | 4.7534 | 0.635719 | 0.000591597 | 3.85774e-05 | 1.38601e-06 | 2(Loss) | true |
