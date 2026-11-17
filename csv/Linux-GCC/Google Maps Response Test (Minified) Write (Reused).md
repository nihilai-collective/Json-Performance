
----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16205.9 | 0.0844637 | 75.6263ms | 11812 | 160 | 55.1522 | 695.106 | 0.024271 | 0.146942 | 1(Win) | true |
| simdjson (reflection) | 12324.1 | 0.0756242 | 93.8276ms | 11812 | 80 | 38.2253 | 914.05 | 0.0437804 | 0.194986 | 2(Loss) | true |
| Glaze | 4277.45 | 0.143225 | 269.72ms | 11812 | 30 | 426.809 | 2633.53 | 0.135616 | 0.572878 | 3(Loss) | true |
