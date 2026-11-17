
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1382.66 | 0.359024 | 5537.88ms | 4506447 | 80 | 9.96267e+09 | 3.10828e+06 | 0.0999815 | 1.79053 | 1(Win) | true |
| simdjson (ondemand) | 1337.92 | 0.372525 | 5594.6ms | 4506447 | 80 | 1.14553e+10 | 3.21221e+06 | 0.341014 | 1.85042 | 2(Loss) | true |
