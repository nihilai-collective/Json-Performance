
----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1095.98 | 0.473664 | 6842.79ms | 4212000 | 80 | 2.41101e+10 | 3.66508e+06 | 0.226085 | 2.77258 | 1(Win) | true |
| simdjson (ondemand) | 1006.04 | 0.484953 | 7350.17ms | 4212000 | 40 | 1.4997e+10 | 3.99276e+06 | 0.049113 | 3.02062 | 2(Loss) | true |
