
----
### Random Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 846.817 | 0.442441 | 560.707ms | 4926 | 640 | 385569 | 5547.6 | 0.151188 | 1(Win) | true |
| simdjson (ondemand) | 515.862 | 0.518399 | 852.127ms | 4926 | 2560 | 5.70546e+06 | 9106.7 | 0.212382 | 2(Loss) | true |
