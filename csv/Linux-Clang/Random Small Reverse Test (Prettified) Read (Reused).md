
----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1376.97 | 0.0811574 | 1332.1ms | 8150 | 40 | 839.426 | 5644.6 | 0.00118106 | 3.76913 | 16.0353 | 3.15865 | 0.0065092 | 1.53374e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 818.911 | 0.03946 | 1716.96ms | 8150 | 1280 | 17954.2 | 9491.19 | 0.0193892 | 6.31913 | 28.3697 | 5.0362 | 0.014255 | 2.55943e-05 | 6.80598e-06 | 2(Loss) | true |
