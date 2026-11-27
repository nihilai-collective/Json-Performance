
----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1499.73 | 0.020034 | 8009.21ms | 94653 | 4890 | 711035 | 60189.7 | 0.014471 | 3.39219 | 16.7003 | 3.34441 | 0.00707167 | 1.2289e-05 | 6.59172e-06 | 1(Win) | true |
| simdjson (ondemand) | 821.938 | 0.0326414 | 6626.75ms | 94653 | 2560 | 3.28978e+06 | 109823 | 0.104617 | 6.17091 | 31.3085 | 6.1861 | 0.00965521 | 3.73816e-05 | 2.70561e-05 | 2(Loss) | true |
