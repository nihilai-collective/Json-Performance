
----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3117.54 | 0.23784 | 5013.78ms | 10548466 | 30 | 1.76704e+09 | 3.22684e+06 | 1.19539 | 0.974745 | 1(Win) | true |
| Jsonifier (generic) | 2994.99 | 0.287484 | 5133.41ms | 10548466 | 30 | 2.79728e+09 | 3.35888e+06 | 0.337265 | 1.01475 | 2(Loss) | true |
