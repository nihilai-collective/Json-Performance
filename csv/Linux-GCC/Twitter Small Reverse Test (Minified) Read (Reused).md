
----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 834.099 | 0.0598319 | 1050.58ms | 2821 | 1280 | 4767.02 | 3225.42 | 0.0126421 | 6.24761 | 25.8196 | 4.81106 | 0.00204133 | 5.78806e-05 | 6.64658e-06 | 1(Win) | true |
| simdjson (ondemand) | 406.032 | 0.104312 | 1386.01ms | 2821 | 640 | 30572.7 | 6625.87 | 0.023317 | 12.746 | 58.503 | 11.7813 | 0.0103908 | 6.25886e-05 | 1.71703e-05 | 2(Loss) | true |
