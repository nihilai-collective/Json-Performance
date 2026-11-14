
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3066.83 | 0.241519 | 843.03ms | 3770 | 30 | 240.506 | 1172.33 | 0.0909039 | 1.76809 | 6.81167 | 1.11989 | 0.000831123 | 6.18921e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2878.27 | 0.176423 | 848.05ms | 3770 | 80 | 388.525 | 1249.14 | 0.189489 | 1.88168 | 7.13634 | 1.09284 | 0.000331565 | 2.65252e-05 | 1.32626e-05 | 2(Loss) | true |
