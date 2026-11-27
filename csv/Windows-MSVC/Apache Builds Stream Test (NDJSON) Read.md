
----
### Apache Builds Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 853.848 | 1.63935 | 5910.62ms | 4212000 | 40 | 2.37913e+11 | 4.70444e+06 | 0.609583 | 2.89941 | 1(Win) | true |
| Jsonifier (generic) DID NOT CONVERGE | 794.485 | 1.43628 | 6469.43ms | 4212000 | 30 | 1.58199e+11 | 5.05595e+06 | 5.1946 | 3.11612 | -(Loss) | false |
