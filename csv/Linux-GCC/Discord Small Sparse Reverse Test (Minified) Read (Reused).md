
----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3527.02 | 0.132699 | 853.942ms | 4857 | 80 | 242.967 | 1313.29 | 0.0943181 | 1.50357 | 6.6327 | 1.13609 | 0.00115812 | 1.02944e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2354.94 | 0.0781328 | 925.523ms | 4857 | 1280 | 3023.1 | 1966.92 | 0.0274934 | 2.2175 | 9.68334 | 1.58061 | 0.00354964 | 3.29743e-05 | 1.33506e-05 | 2(Loss) | true |
