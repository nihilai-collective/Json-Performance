
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 22098.8 | 0.0384963 | 367.422ms | 83958 | 160 | 311.275 | 3623.21 | 0.0600657 | 0.111198 | 1(Win) | true |
| simdjson (stage-1) | 20260.8 | 0.0359774 | 400.286ms | 83958 | 30 | 60.6448 | 3951.9 | 0.0497899 | 0.121362 | 2(Loss) | true |
