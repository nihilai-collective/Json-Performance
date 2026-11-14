
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2450.05 | 0.122228 | 4343.15ms | 83958 | 30 | 47867.4 | 32680.4 | 0.0832996 | 2.10414 | 9.51012 | 1.76283 | 0.00406394 | 5.55833e-06 | 3.17619e-06 | 1(Win) | true |
| simdjson (ondemand) | 2095.4 | 0.017463 | 4911.12ms | 83958 | 4890 | 217738 | 38211.6 | 0.168929 | 2.44847 | 10.285 | 1.59742 | 0.00756737 | 8.80273e-06 | 3.43925e-06 | 2(Loss) | true |
