
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 368.486 | 0.13918 | 491.417ms | 1811 | 30 | 1276.65 | 4687.03 | 0.0646757 | 6.67585 | 1(Win) | true |
| simdjson (ondemand) | 290.709 | 0.0459376 | 600.518ms | 1811 | 30 | 223.448 | 5941 | 0.00336632 | 8.47616 | 2(Loss) | true |
