
----
### Marine IK Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4403.78 | 0.20263 | 822.52ms | 4604 | 30 | 122.447 | 997.033 | 0.0401029 | 1.21492 | 6.14053 | 0.971329 | 0.000434405 | 7.24008e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3904.2 | 0.0628022 | 835.101ms | 4604 | 2560 | 1277.01 | 1124.61 | 0.0286822 | 1.36199 | 6.96829 | 0.960252 | 0.000435168 | 3.30894e-05 | 1.46781e-05 | 2(Loss) | true |
