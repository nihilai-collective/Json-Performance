
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2406.44 | 0.0192981 | 8206.82ms | 183677 | 4890 | 964938 | 72791.4 | 0.192906 | 2.11977 | 9.18002 | 1.73476 | 0.00182847 | 1.23628e-05 | 8.8657e-06 | 1(Win) | true |
| simdjson (ondemand) | 2399.19 | 0.108953 | 8207.81ms | 183677 | 80 | 506233 | 73011.4 | 0.0283255 | 2.10775 | 9.92847 | 1.4099 | 0.00367398 | 2.04163e-05 | 1.66052e-05 | 2(Loss) | true |
