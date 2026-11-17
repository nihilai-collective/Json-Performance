
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3778.28 | 0.0944321 | 124.938ms | 4669 | 30 | 37.1552 | 1178.5 | 0.0480606 | 0.640366 | 1(Win) | true |
| Jsonifier (two-stage) | 2638.68 | 0.0688054 | 175.829ms | 4669 | 80 | 107.847 | 1687.47 | 0.255645 | 0.923809 | 2(Loss) | true |
| Glaze | 1757.47 | 0.0368118 | 257.038ms | 4669 | 160 | 139.176 | 2533.58 | 0.0510902 | 1.39364 | 3(Loss) | true |
| simdjson (reflection) | 1536.65 | 0.100149 | 300.398ms | 4669 | 30 | 252.644 | 2897.67 | 0.077133 | 1.59577 | 4(Loss) | true |
| simdjson (ondemand) | 1027.13 | 0.162085 | 439.882ms | 4669 | 4890 | 241428 | 4335.09 | 0.277132 | 2.39529 | 5(Loss) | true |
