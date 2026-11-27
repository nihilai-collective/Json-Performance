
----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1055.36 | 0.230802 | 7438.81ms | 4506447 | 80 | 7.06705e+09 | 4.07225e+06 | 0.29014 | 1(Win) | true |
| simdjson (ondemand) | 645.205 | 0.99706 | 5199.17ms | 4506447 | 30 | 1.32324e+11 | 6.66096e+06 | 2.25903 | 2(Loss) | true |
