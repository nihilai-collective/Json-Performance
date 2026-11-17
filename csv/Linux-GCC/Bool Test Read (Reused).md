
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 410.86 | 0.69707 | 215.412ms | 905 | 640 | 137228 | 2100.65 | 0.522759 | 5.95039 | 1(Win) | true |
| simdjson (ondemand) | 216.489 | 0.0639012 | 414.363ms | 905 | 30 | 194.7 | 3986.7 | 0.00919809 | 11.3603 | 2(Loss) | true |
