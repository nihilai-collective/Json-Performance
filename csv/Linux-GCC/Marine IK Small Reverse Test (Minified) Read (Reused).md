
----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 339.468 | 0.0433924 | 2107.55ms | 4604 | 4890 | 154031 | 12934.1 | 0.023605 | 15.2027 | 62.9913 | 13.6979 | 0.022259 | 8.51931e-05 | 2.11872e-05 | 1(Win) | true |
| simdjson (ondemand) | 255.387 | 0.0319417 | 2530.35ms | 4604 | 2560 | 77202.1 | 17192.4 | 0.144257 | 20.197 | 101.151 | 21.1232 | 0.0225011 | 0.000110128 | 4.32708e-05 | 2(Loss) | true |
