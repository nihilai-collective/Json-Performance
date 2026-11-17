
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2639.26 | 0.263268 | 876.18ms | 3808 | 4890 | 64170.4 | 1375.99 | 0.302188 | 1.97422 | 6.81749 | 1.02521 | 0.000531547 | 7.22835e-05 | 3.37788e-05 | 1(Win) | true |
| Glaze | 2570.83 | 0.347236 | 879.017ms | 3808 | 640 | 15398.5 | 1412.62 | 0.265862 | 2.03521 | 8.31276 | 1.47269 | 0.000304047 | 4.88281e-05 | 3.28256e-06 | 2(Loss) | true |
| Jsonifier | 1790.44 | 0.313623 | 942.006ms | 3808 | 4890 | 197879 | 2028.33 | 0.145255 | 2.88768 | 7.09743 | 1.35084 | 0.000536702 | 6.82558e-05 | 3.11474e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1302.62 | 0.112064 | 1024.84ms | 3808 | 4890 | 47731.1 | 2787.91 | 0.440049 | 3.93256 | 13.1762 | 2.19958 | 0.000412059 | 5.27358e-05 | 1.53589e-05 | 4(Loss) | true |
