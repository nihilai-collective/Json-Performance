
----
### Marine IK Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 335.888 | 0.0262673 | 2031.6ms | 4604 | 2560 | 30182.4 | 13072 | 0.115052 | 15.3323 | 66.1073 | 14.5241 | 0.0197671 | 0.000431096 | 0.000289151 | 1(Win) | true |
| simdjson (ondemand) | 234.044 | 0.200766 | 2574.69ms | 4604 | 40 | 56743.8 | 18760.2 | 0.232266 | 21.6228 | 105.535 | 22.0936 | 0.0257711 | 0.000135752 | 5.43006e-05 | 2(Loss) | true |
