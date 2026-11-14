
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2200.8 | 0.146702 | 840.083ms | 2821 | 640 | 2058.24 | 1222.43 | 0.152978 | 2.41147 | 9.134 | 1.63417 | 0.000362792 | 6.59119e-05 | 1.10776e-05 | 1(Win) | true |
| simdjson (ondemand) | 2074.46 | 0.0436862 | 846.14ms | 2821 | 4890 | 1569.62 | 1296.88 | 0.16328 | 2.5575 | 9.43921 | 1.54272 | 0.000362748 | 4.13202e-05 | 3.04465e-06 | 2(Loss) | true |
