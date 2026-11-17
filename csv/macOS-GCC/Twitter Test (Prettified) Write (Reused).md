
----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15680.9 | 0.52638 | 4426.33ms | 716365 | 640 | 3.36593e+07 | 43567.6 | 0.595955 | 1(Win) | true |
| Glaze | 4669.28 | 0.20559 | 8202.43ms | 716365 | 80 | 7.23873e+06 | 146314 | 0.0766065 | 2(Loss) | true |
| simdjson (reflection) | 348.833 | 0.967425 | 5975.26ms | 716365 | 30 | 1.07693e+10 | 1.95847e+06 | 1.63381 | 3(Loss) | true |
