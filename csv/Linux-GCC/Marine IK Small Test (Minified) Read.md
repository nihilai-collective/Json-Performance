
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 924.118 | 0.102512 | 1203.81ms | 4604 | 40 | 948.91 | 4751.25 | 0.116948 | 5.62892 | 23.8388 | 5.20135 | 0.00355669 | 4.34405e-05 | 1.62902e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 772.935 | 0.0401222 | 1296.07ms | 4604 | 2560 | 13298.3 | 5680.57 | 0.0615551 | 6.70014 | 28.163 | 5.60024 | 0.00409223 | 9.20565e-05 | 5.75247e-05 | 2(Loss) | true |
| Glaze | 639.812 | 0.0865386 | 1408.92ms | 4604 | 1280 | 45143.5 | 6862.51 | 0.120215 | 8.00023 | 33.7823 | 6.94593 | 0.00547147 | 8.4675e-05 | 5.03978e-05 | 3(Loss) | true |
| simdjson (reflection) | 622.651 | 0.0897959 | 1432.78ms | 4604 | 4890 | 196066 | 7051.64 | 0.0267359 | 8.27621 | 31.0638 | 5.96481 | 0.00470454 | 0.00011482 | 5.95641e-05 | 4(Loss) | true |
| simdjson (ondemand) | 491.845 | 0.116896 | 1628.88ms | 4604 | 40 | 4355.87 | 8927.02 | 0.100436 | 10.5231 | 37.6419 | 7.66442 | 0.00882928 | 6.51607e-05 | 0 | 5(Loss) | true |
