
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10667 | 0.261182 | 749.504ms | 2632 | 2560 | 966.971 | 235.312 | 0.166612 | 0.556803 | 1.74071 | 0.263719 | 0.000383204 | 2.28557e-05 | 2.07779e-06 | 1(Win) | true |
| Glaze | 3621.66 | 0.187311 | 794.276ms | 2632 | 2560 | 4314.43 | 693.073 | 0.0563931 | 1.48447 | 4.30509 | 0.647417 | 0.000386766 | 3.93296e-05 | 1.27636e-05 | 2(Loss) | true |
