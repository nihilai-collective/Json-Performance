
----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12471.3 | 0.0893299 | 25.2355ms | 2963 | 640 | 26.219 | 226.58 | 0.124974 | 0.175389 | 1(Win) | true |
| simdjson (reflection) | 8978.97 | 0.0942072 | 34.5691ms | 2963 | 640 | 56.2547 | 314.706 | 0.208094 | 0.253657 | 2(Loss) | true |
| Glaze | 5107.8 | 0.0845351 | 57.6975ms | 2963 | 640 | 139.975 | 553.22 | 0.0296471 | 0.461544 | 3(Loss) | true |
