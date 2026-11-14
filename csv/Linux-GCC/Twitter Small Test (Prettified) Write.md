
----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12088.9 | 0.0653317 | 753.599ms | 4300 | 640 | 31.4334 | 339.22 | 0.588408 | 0.471178 | 1.06419 | 0.16186 | 0.000232558 | 2.68895e-05 | 1.81686e-06 | 1(Win) | true |
| Glaze | 3647.69 | 0.206637 | 834.809ms | 4300 | 4890 | 26389.1 | 1124.22 | 0.577605 | 1.46325 | 3.57698 | 0.599535 | 0.000301232 | 9.39269e-05 | 3.39563e-05 | 2(Loss) | true |
| simdjson (reflection) | 549.554 | 0.184224 | 1480.47ms | 4300 | 640 | 120945 | 7462.05 | 0.372194 | 9.34218 | 34.0658 | 7.50628 | 0.00980196 | 0.000193314 | 9.15698e-05 | 3(Loss) | true |
