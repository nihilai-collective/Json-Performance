
----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1130.46 | 0.017769 | 8725.76ms | 94653 | 4890 | 984450 | 79850.7 | 0.0578396 | 4.53621 | 20.6428 | 4.21044 | 0.0107707 | 1.74461e-05 | 1.29976e-05 | 1(Win) | true |
| simdjson (ondemand) | 709.058 | 0.0672392 | 6876.95ms | 94653 | 320 | 2.34476e+06 | 127307 | 0.222612 | 7.17784 | 34.1199 | 7.06221 | 0.0122895 | 6.60307e-06 | 2.01394e-06 | 2(Loss) | true |
