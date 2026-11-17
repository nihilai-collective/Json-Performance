
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1561.76 | 0.116414 | 10109.2ms | 4506447 | 40 | 4.10494e+08 | 2.75181e+06 | 0.0382387 | 3.24122 | 15.2693 | 2.85088 | 0.00869347 | 0.0808973 | 0.00287212 | 1(Win) | true |
| simdjson (ondemand) | 1160.74 | 0.100643 | 6328.06ms | 4506447 | 80 | 1.11086e+09 | 3.70253e+06 | 0.234979 | 4.37959 | 17.1579 | 3.15325 | 0.0133964 | 0.0788828 | 0.00198667 | 2(Loss) | true |
