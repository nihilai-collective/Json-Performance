
----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1449.18 | 0.154467 | 8183.29ms | 94653 | 80 | 740601 | 62288.9 | 0.000200678 | 3.51758 | 16.8554 | 3.34383 | 0.00788617 | 3.96184e-06 | 1.32061e-07 | 1(Win) | true |
| simdjson (ondemand) | 833.297 | 0.175337 | 6584.66ms | 94653 | 40 | 1.44303e+06 | 108326 | 0.0572363 | 6.17831 | 30.3799 | 6.20631 | 0.00969356 | 0.00018964 | 0.000176434 | 2(Loss) | true |
