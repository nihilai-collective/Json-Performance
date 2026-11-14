
----
### Apache Builds Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2193.59 | 0.0397835 | 5340.51ms | 94653 | 4890 | 1.31061e+06 | 41150.9 | 0.403756 | 2.31567 | 10.8438 | 2.07789 | 0.00692853 | 4.44633e-06 | 1.64199e-06 | 1(Win) | true |
| simdjson (ondemand) | 1859.63 | 0.0349071 | 6063.13ms | 94653 | 1280 | 367499 | 48541 | 0.154439 | 2.75626 | 11.3923 | 2.0817 | 0.00762393 | 3.19423e-06 | 4.86976e-07 | 2(Loss) | true |
