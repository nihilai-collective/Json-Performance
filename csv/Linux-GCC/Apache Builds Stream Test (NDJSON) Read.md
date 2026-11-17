
----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2070.55 | 0.191277 | 7867ms | 4212000 | 40 | 5.50792e+08 | 1.94e+06 | 0.0556735 | 2.44149 | 11.3164 | 2.01977 | 0.0116455 | 0.0663117 | 0.0078696 | 1(Win) | true |
| simdjson (ondemand) | 1534.28 | 0.136873 | 9972.25ms | 4212000 | 30 | 3.85236e+08 | 2.61809e+06 | 0.0725572 | 3.30921 | 12.6013 | 2.34243 | 0.012492 | 0.0662127 | 0.00575204 | 2(Loss) | true |
