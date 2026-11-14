
----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 326.707 | 0.0938783 | 2067.63ms | 4604 | 160 | 25468.5 | 13439.3 | 0.00186025 | 15.8091 | 68.9156 | 14.5793 | 0.0201863 | 0.000126249 | 7.73784e-05 | 1(Win) | true |
| simdjson (ondemand) | 224.099 | 0.0497638 | 2685.39ms | 4604 | 640 | 60841.2 | 19592.7 | 0.0678681 | 23.0175 | 109.233 | 21.907 | 0.0240423 | 8.00934e-05 | 2.5114e-05 | 2(Loss) | true |
