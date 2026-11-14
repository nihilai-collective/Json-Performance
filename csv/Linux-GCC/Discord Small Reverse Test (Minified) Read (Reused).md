
----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 773.953 | 0.0874567 | 1343.84ms | 4857 | 640 | 17533.7 | 5984.85 | 0.0408489 | 6.69148 | 28.1513 | 5.57608 | 0.00748662 | 4.56815e-05 | 6.75571e-06 | 1(Win) | true |
| simdjson (ondemand) | 246.382 | 0.019525 | 2624.57ms | 4857 | 2560 | 34493.9 | 18800.1 | 0.0672699 | 20.9253 | 105.085 | 22.097 | 0.0482539 | 4.71291e-05 | 8.92719e-06 | 2(Loss) | true |
