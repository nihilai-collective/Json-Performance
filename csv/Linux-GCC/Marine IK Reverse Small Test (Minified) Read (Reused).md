
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1067.01 | 0.0724686 | 1216.23ms | 4604 | 1280 | 11382.6 | 4114.97 | 0.0165012 | 4.87183 | 19.6227 | 4.13081 | 0.00478626 | 5.87125e-05 | 1.34055e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 893.371 | 0.0759021 | 1297.62ms | 4604 | 40 | 556.64 | 4914.77 | 0.0395223 | 5.81685 | 23.4844 | 4.55387 | 0.00330691 | 9.2311e-05 | 0 | 2(Loss) | true |
| Glaze | 760.358 | 0.0565215 | 1385.51ms | 4604 | 1280 | 13635.6 | 5774.54 | 0.0707348 | 6.81705 | 29.1901 | 5.89346 | 0.00451425 | 3.83498e-05 | 1.05207e-05 | 3(Loss) | true |
| simdjson (reflection) | 720.78 | 0.0530987 | 1423.99ms | 4604 | 1280 | 13391.9 | 6091.62 | 0.13676 | 7.1905 | 27.1212 | 5.09514 | 0.00484277 | 9.01051e-05 | 3.15622e-05 | 4(Loss) | true |
| simdjson (ondemand) | 542.789 | 0.0705639 | 1638.2ms | 4604 | 1280 | 41704.6 | 8089.18 | 0.0964602 | 9.51701 | 33.0174 | 6.61569 | 0.0160504 | 7.00817e-05 | 1.54417e-05 | 5(Loss) | true |
