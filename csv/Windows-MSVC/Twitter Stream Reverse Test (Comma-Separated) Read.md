
----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 595.832 | 0.370782 | 5007.51ms | 4219119 | 40 | 2.5078e+10 | 6.75302e+06 | 0.133564 | 5.10099 | 1(Win) | true |
| simdjson (ondemand) | 214.966 | 0.191291 | 5713.23ms | 4219119 | 30 | 3.84606e+10 | 1.87177e+07 | 0.00470166 | 14.139 | 2(Loss) | true |
