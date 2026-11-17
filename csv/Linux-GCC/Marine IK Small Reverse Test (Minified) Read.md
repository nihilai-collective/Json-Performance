
----
### Marine IK Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 323.051 | 0.0544552 | 2095.44ms | 4604 | 320 | 17529 | 13591.4 | 0.0134984 | 15.9896 | 66.7743 | 14.5406 | 0.0237171 | 0.000793468 | 0.000397073 | 1(Win) | true |
| simdjson (ondemand) | 241.541 | 0.0925377 | 2538.5ms | 4604 | 80 | 22636.8 | 18177.9 | 0.0248179 | 21.3607 | 105.179 | 22.0321 | 0.025391 | 9.2311e-05 | 3.25804e-05 | 2(Loss) | true |
