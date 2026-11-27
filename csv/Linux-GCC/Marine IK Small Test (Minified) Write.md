
----
### Marine IK Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1919.66 | 0.0737447 | 964.36ms | 4918 | 4890 | 15874.5 | 2443.23 | 0.0832177 | 2.71742 | 9.67629 | 0.818829 | 0.000548713 | 8.66563e-05 | 3.67998e-05 | 1(Win) | true |
| Jsonifier | 1436.25 | 0.167551 | 1048.06ms | 4918 | 2560 | 76639 | 3265.56 | 0.10962 | 3.62847 | 9.11001 | 0.492274 | 0.00044265 | 7.79185e-05 | 3.7331e-05 | 2(Loss) | true |
| Glaze | 1227.04 | 0.141389 | 1084.87ms | 4604 | 320 | 8190.92 | 3578.3 | 0.0518147 | 4.24211 | 12.7118 | 1.08384 | 0.000659074 | 2.71503e-05 | 0 | 3(Loss) | true |
