
----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 813.074 | 0.0901471 | 1362.08ms | 4630 | 80 | 1917.32 | 5430.64 | 0.0195688 | 6.39225 | 32.5683 | 6.17084 | 0.00394708 | 0.000156587 | 2.15983e-05 | 1(Win) | true |
| simdjson (ondemand) | 779.615 | 0.0344543 | 1383.78ms | 4630 | 4890 | 18620.8 | 5663.71 | 0.0704251 | 6.65241 | 33.0344 | 5.76653 | 0.00267766 | 5.9318e-05 | 1.24554e-05 | 2(Loss) | true |
