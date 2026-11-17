
----
### Marine IK Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2551.81 | 0.157186 | 890.851ms | 4604 | 640 | 4681.43 | 1720.62 | 0.0254333 | 2.06226 | 9.16182 | 1.6503 | 0.00108601 | 2.78291e-05 | 1.15389e-05 | 1(Win) | true |
| simdjson (ondemand) | 1887.46 | 0.0693355 | 953.505ms | 4604 | 2560 | 6659.88 | 2326.26 | 0.092539 | 2.76737 | 13.2848 | 2.35274 | 0.00136116 | 2.90169e-05 | 6.10882e-06 | 2(Loss) | true |
