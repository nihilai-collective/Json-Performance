
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 787.526 | 0.030713 | 470.686ms | 3862 | 80 | 165.056 | 4676.79 | 0.134086 | 3.12526 | 1(Win) | true |
| simdjson (ondemand) | 455.036 | 0.0864072 | 811.21ms | 3862 | 4890 | 239190 | 8094.07 | 0.260752 | 5.42259 | 2(Loss) | true |
