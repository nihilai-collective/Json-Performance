
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1771.27 | 0.163003 | 8801.48ms | 5212421 | 30 | 6.27805e+08 | 2.80644e+06 | 0.112259 | 2.86458 | 13.4729 | 2.30229 | 0.0103707 | 0.0614223 | 0.000274268 | 1(Win) | true |
| Jsonifier (generic) | 1732.06 | 0.83306 | 8901.07ms | 5212421 | 40 | 2.28646e+10 | 2.86996e+06 | 0.807521 | 2.93371 | 13.8811 | 2.60521 | 0.0103597 | 0.0604341 | 7.05814e-05 | 2(Loss) | true |
