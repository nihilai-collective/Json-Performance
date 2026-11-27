
----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1908.65 | 0.0377167 | 904.762ms | 3370 | 4890 | 1972.35 | 1683.85 | 0.210112 | 2.74867 | 11.576 | 2.18042 | 0.00222655 | 4.73321e-05 | 9.83051e-06 | 1(Win) | true |
| simdjson (ondemand) | 953.269 | 0.109391 | 1072.48ms | 3370 | 30 | 408.047 | 3371.43 | 0.382149 | 5.36843 | 21.6955 | 4.29347 | 0.00939664 | 0 | 0 | 2(Loss) | true |
