
----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2139.77 | 0.513223 | 6672.01ms | 4219120 | 160 | 1.49019e+10 | 1.88042e+06 | 0.619531 | 1.157 | 1(Win) | true |
| Jsonifier (generic) | 1872.38 | 0.294637 | 7396.54ms | 4219120 | 160 | 6.41432e+09 | 2.14896e+06 | 0.411209 | 1.32225 | 2(Loss) | true |
