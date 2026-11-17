
----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1419.75 | 0.0209346 | 9121.19ms | 124597 | 2560 | 785886 | 83694.1 | 0.145286 | 3.57946 | 16.5617 | 3.28644 | 0.00830874 | 2.57549e-05 | 1.57163e-05 | 1(Win) | true |
| simdjson (ondemand) | 912.162 | 0.0576406 | 6964.58ms | 124597 | 80 | 451044 | 130267 | 0.0916552 | 5.5408 | 26.6776 | 5.30834 | 0.0117229 | 1.60518e-05 | 1.06343e-05 | 2(Loss) | true |
