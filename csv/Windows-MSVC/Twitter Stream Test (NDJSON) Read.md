
----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 990.501 | 0.999542 | 9179.12ms | 4219120 | 40 | 6.59472e+10 | 4.06226e+06 | 1.64309 | 2.49943 | 1(Win) | true |
| simdjson (ondemand) | 838.623 | 0.944384 | 10287.8ms | 4219120 | 80 | 1.64247e+11 | 4.79794e+06 | 0.821186 | 2.95205 | 2(Loss) | true |
