
----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1554.09 | 0.0694029 | 898.891ms | 2632 | 2560 | 3216.72 | 1615.13 | 0.00207998 | 3.34558 | 14.1094 | 2.68617 | 0.00289333 | 5.19448e-05 | 1.57319e-05 | 1(Win) | true |
| simdjson (ondemand) | 751.453 | 0.0293167 | 1067.66ms | 2632 | 4890 | 4689.3 | 3340.29 | 0.0297113 | 6.85039 | 27.7063 | 5.55737 | 0.010076 | 7.91734e-05 | 2.65724e-05 | 2(Loss) | true |
