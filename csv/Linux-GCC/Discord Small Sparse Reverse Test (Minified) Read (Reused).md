
----
### Discord Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3255.03 | 0.0589554 | 864.178ms | 4857 | 320 | 225.228 | 1423.03 | 0.0373185 | 1.62628 | 6.94667 | 1.19971 | 0.00109185 | 2.12322e-05 | 2.57361e-06 | 1(Win) | true |
| simdjson (ondemand) | 2397.87 | 0.0283745 | 914.764ms | 4857 | 4890 | 1469.1 | 1931.72 | 0.0245368 | 2.19276 | 9.69405 | 1.58514 | 0.0025374 | 1.701e-05 | 2.1052e-06 | 2(Loss) | true |
