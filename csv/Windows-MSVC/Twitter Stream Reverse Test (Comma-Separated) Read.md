
----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 562.001 | 0.999847 | 10963.6ms | 4219119 | 80 | 4.09946e+11 | 7.15954e+06 | 3.53456 | 5.4077 | -(Win) | false |
| simdjson (ondemand) DID NOT CONVERGE | 191.005 | 2.46487 | 6160.57ms | 4219119 | 30 | 8.08844e+12 | 2.10658e+07 | 13.9149 | 15.9127 | -(Loss) | false |
