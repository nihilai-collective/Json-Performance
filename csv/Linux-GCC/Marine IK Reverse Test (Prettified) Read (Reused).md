
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1363.31 | 0.328076 | 8175.04ms | 7351818 | 40 | 1.13869e+10 | 5.14279e+06 | 0.172642 | 3.73672 | 15.2754 | 3.20597 | 0.0107995 | 0.180269 | 0.00516621 | 1(Win) | true |
| simdjson (ondemand) | 942.359 | 0.187198 | 5386.22ms | 7351818 | 40 | 7.75921e+09 | 7.44009e+06 | 0.278742 | 5.38891 | 25.708 | 5.14811 | 0.0123912 | 0.429783 | 0.00181287 | 2(Loss) | true |
