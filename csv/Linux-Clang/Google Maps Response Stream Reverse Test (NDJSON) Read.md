
----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 781.104 | 0.965145 | 8114.21ms | 4203059 | 30 | 7.35901e+10 | 5.13164e+06 | 0.9807 | 6.51769 | 27.6601 | 5.54107 | 0.0253115 | 0.0883215 | 0.0100705 | 1(Win) | true |
| simdjson (ondemand) | 725.286 | 0.666087 | 8770.28ms | 4203059 | 40 | 5.42043e+10 | 5.52658e+06 | 0.279452 | 6.99725 | 28.3948 | 5.06159 | 0.0274623 | 0.0880782 | 0.0142582 | 2(Loss) | true |
