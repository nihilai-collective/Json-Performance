
----
### Discord Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11564 | 0.237619 | 774.45ms | 4857 | 4890 | 4429.85 | 400.552 | 0.757805 | 0.4853 | 1.57175 | 0.261684 | 0.000206562 | 3.322e-05 | 5.51562e-06 | 1(Win) | true |
| Glaze | 2969.65 | 0.174405 | 894.54ms | 4857 | 4890 | 36187 | 1559.78 | 0.0252928 | 1.7432 | 3.68581 | 0.525428 | 0.000210941 | 2.57255e-05 | 3.1999e-06 | 2(Loss) | true |
