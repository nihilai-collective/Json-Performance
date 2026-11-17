
----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 346.057 | 0.0314531 | 2096.83ms | 4604 | 1280 | 20385.1 | 12687.9 | 0.110515 | 14.9243 | 62.543 | 13.5838 | 0.0213542 | 8.39963e-05 | 3.30894e-05 | 1(Win) | true |
| simdjson (ondemand) | 256.332 | 0.0407638 | 2528.47ms | 4604 | 640 | 31202.8 | 17129 | 0.0621408 | 20.1374 | 100.921 | 21.0734 | 0.0235437 | 5.76944e-05 | 1.2557e-05 | 2(Loss) | true |
