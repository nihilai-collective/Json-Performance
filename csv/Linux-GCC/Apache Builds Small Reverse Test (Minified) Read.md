
----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1248.24 | 0.0524409 | 918.844ms | 2632 | 2560 | 2846.79 | 2010.89 | 0.0406158 | 4.20742 | 16.5034 | 3.24506 | 0.00318155 | 6.94576e-05 | 2.24105e-05 | 1(Win) | true |
| simdjson (ondemand) | 717.119 | 0.0397263 | 1070.62ms | 2632 | 4890 | 9454.84 | 3500.22 | 0.0455018 | 7.25772 | 29.5144 | 5.97493 | 0.0131326 | 4.87161e-05 | 1.50733e-05 | 2(Loss) | true |
