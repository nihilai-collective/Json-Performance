
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1159.01 | 0.271801 | 6228.71ms | 4506447 | 80 | 8.12614e+09 | 3.70806e+06 | 2.05197 | 1(Win) | true |
| simdjson (ondemand) | 696.7 | 0.516818 | 9895.55ms | 4506447 | 80 | 8.13099e+10 | 6.16863e+06 | 4.15439 | 2(Loss) | true |
