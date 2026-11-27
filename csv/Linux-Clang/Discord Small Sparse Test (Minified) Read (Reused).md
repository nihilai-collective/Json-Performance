
----
### Discord Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4749.33 | 0.134978 | 817.797ms | 4857 | 1280 | 2218.24 | 975.294 | 0.151144 | 1.13049 | 4.89994 | 0.738522 | 0.000434778 | 2.26799e-05 | 6.27316e-06 | 1(Win) | true |
| simdjson (ondemand) | 4141.12 | 0.145845 | 835.234ms | 4857 | 160 | 425.797 | 1118.54 | 0.054729 | 1.29004 | 5.44328 | 0.700844 | 0.000976683 | 1.80152e-05 | 6.43401e-06 | 2(Loss) | true |
