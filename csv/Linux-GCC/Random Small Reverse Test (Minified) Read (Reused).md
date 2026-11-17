
----
### Random Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 915.375 | 0.169344 | 1277.23ms | 4926 | 160 | 12085.1 | 5132.11 | 0.142647 | 5.66706 | 24.8238 | 4.93037 | 0.00952218 | 5.07511e-05 | 2.53756e-06 | 1(Win) | true |
| simdjson (ondemand) | 538.089 | 0.0600559 | 1634.12ms | 4926 | 320 | 8797.13 | 8730.52 | 0.0518207 | 9.61765 | 42.8473 | 8.53005 | 0.0184353 | 0.000111652 | 6.40733e-05 | 2(Loss) | true |
