
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 6125.5 | 1.03643 | 9605.75ms | 9930848 | 40 | 1.02714e+10 | 1.54612e+06 | 6.77933 | -(Win) | false |
| Glaze DID NOT CONVERGE | 2627.33 | 0.582344 | 5654.35ms | 9930228 | 30 | 1.32181e+10 | 3.6045e+06 | 8.42471 | -(Loss) | false |
| simdjson (reflection) DID NOT CONVERGE | 283.982 | 1.67237 | 10675.2ms | 10018896 | 30 | 9.49832e+12 | 3.36457e+07 | 5.32497 | -(Loss) | false |
