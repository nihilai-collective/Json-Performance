
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 751.467 | 0.342212 | 496.469ms | 3862 | 640 | 180043 | 4901.2 | 0.105984 | 1(Win) | true |
| simdjson (ondemand) | 474.209 | 0.298293 | 790.092ms | 3862 | 640 | 343518 | 7766.8 | 0.139247 | 2(Loss) | true |
