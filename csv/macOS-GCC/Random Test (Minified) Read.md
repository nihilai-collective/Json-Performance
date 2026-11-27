
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 7989.29 | 0.127577 | 5592.76ms | 461466 | 640 | 3.16074e+06 | 55084.8 | 0.00580956 | 1(Win) | true |
| simdjson (stage-1) | 5708.91 | 0.345953 | 7401.22ms | 461466 | 80 | 5.68981e+06 | 77088 | 0.116366 | 2(Loss) | true |
