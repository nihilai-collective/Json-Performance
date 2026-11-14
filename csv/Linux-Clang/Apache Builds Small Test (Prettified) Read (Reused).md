
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2942.05 | 0.0351085 | 834.811ms | 3370 | 4890 | 719.269 | 1092.39 | 0.0111003 | 1.81553 | 7.52048 | 1.28427 | 0.00059602 | 3.29504e-05 | 3.70161e-06 | 1(Win) | true |
| simdjson (ondemand) | 2434.91 | 0.0587998 | 858.203ms | 3370 | 4890 | 2945.47 | 1319.92 | 0.0208947 | 2.17624 | 8.3905 | 1.35074 | 0.00195099 | 5.12764e-05 | 2.17849e-05 | 2(Loss) | true |
