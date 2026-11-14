
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2357.4 | 0.0332528 | 838.802ms | 2821 | 640 | 92.1675 | 1141.22 | 0.158705 | 2.26339 | 8.57639 | 1.54591 | 0.0003567 | 4.32028e-05 | 1.10776e-05 | 1(Win) | true |
| simdjson (ondemand) | 2137.02 | 0.047666 | 849.93ms | 2821 | 4890 | 1760.82 | 1258.91 | 0.0367325 | 2.48681 | 9.55335 | 1.43602 | 0.000378406 | 7.48839e-05 | 1.88478e-05 | 2(Loss) | true |
