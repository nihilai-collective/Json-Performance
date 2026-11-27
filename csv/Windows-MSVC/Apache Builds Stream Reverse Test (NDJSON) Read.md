
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) DID NOT CONVERGE | 796.023 | 1.66682 | 6507.63ms | 4212000 | 40 | 2.82985e+11 | 5.04618e+06 | 2.56818 | 3.11007 | -(Win) | false |
| Jsonifier (generic) DID NOT CONVERGE | 756.679 | 1.0219 | 6438.49ms | 4212000 | 40 | 1.17715e+11 | 5.30856e+06 | 3.66302 | 3.27182 | -(Loss) | false |
