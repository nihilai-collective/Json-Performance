
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 601.606 | 0.034832 | 1458.37ms | 4604 | 2560 | 16544.1 | 7298.32 | 0.112926 | 8.54002 | 32.9484 | 6.91996 | 0.0108527 | 8.28084e-05 | 3.47863e-05 | 1(Win) | true |
| simdjson (ondemand) | 570.337 | 0.0854171 | 1503.88ms | 4604 | 640 | 27674.4 | 7698.47 | 0.198811 | 9.06564 | 36.3829 | 6.94353 | 0.0119427 | 0.000252837 | 0.000176138 | 2(Loss) | true |
