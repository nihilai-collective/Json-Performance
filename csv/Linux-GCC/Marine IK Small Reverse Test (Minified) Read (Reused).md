
----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 361.935 | 0.0251788 | 2030.83ms | 4604 | 2560 | 23884.6 | 12131.2 | 0.101501 | 14.2283 | 61.8254 | 13.5519 | 0.0187972 | 0.000161884 | 9.01051e-05 | 1(Win) | true |
| simdjson (ondemand) | 251.99 | 0.0878504 | 2560.3ms | 4604 | 320 | 74979.2 | 17424.1 | 0.222274 | 20.3118 | 101.165 | 21.1051 | 0.0260025 | 8.82385e-05 | 4.14042e-05 | 2(Loss) | true |
