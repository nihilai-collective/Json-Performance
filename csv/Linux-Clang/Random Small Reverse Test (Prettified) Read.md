
----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1210.77 | 0.0242476 | 1368.72ms | 8150 | 4890 | 11847.9 | 6419.44 | 0.0147075 | 4.27558 | 17.6528 | 3.51644 | 0.00645221 | 3.63833e-05 | 1.28972e-05 | 1(Win) | true |
| simdjson (ondemand) | 758.874 | 0.101548 | 1766.03ms | 8150 | 320 | 34615.6 | 10242.1 | 0.19394 | 6.82764 | 29.9443 | 5.38577 | 0.0144179 | 3.91104e-05 | 1.22699e-05 | 2(Loss) | true |
