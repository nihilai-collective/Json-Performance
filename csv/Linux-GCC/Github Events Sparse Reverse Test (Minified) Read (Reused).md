
----
### Github Events Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5948.34 | 0.0456605 | 1611.51ms | 53331 | 4890 | 74534.5 | 8550.35 | 0.0813529 | 0.864011 | 4.18563 | 0.667811 | 0.00167604 | 6.28478e-06 | 2.7877e-06 | 1(Win) | true |
| simdjson (ondemand) | 4309.74 | 0.0408664 | 1929.01ms | 53331 | 1280 | 29771.6 | 11801.3 | 0.30442 | 1.18879 | 5.70923 | 0.921566 | 0.00255064 | 3.51578e-06 | 5.85963e-08 | 2(Loss) | true |
