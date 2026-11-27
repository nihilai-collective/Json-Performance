
----
### Twitter Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2970.87 | 0.703595 | 137.376ms | 3808 | 2560 | 189371 | 1222.4 | 0.131062 | 1(Win) | true |
| Jsonifier (two-stage) | 2572.68 | 0.7108 | 159.686ms | 3808 | 2560 | 257726 | 1411.6 | 0.703433 | 2(Loss) | true |
| Glaze | 2413.34 | 0.711724 | 161.998ms | 3808 | 2560 | 293644 | 1504.8 | 0.857909 | 3(Loss) | true |
| simdjson (reflection) | 1933.96 | 0.453417 | 202.698ms | 3808 | 2560 | 185581 | 1877.8 | 0.286746 | 4(Loss) | true |
| simdjson (ondemand) | 1534.91 | 0.583854 | 250.112ms | 3808 | 1280 | 244257 | 2366 | 0.471143 | 5(Loss) | true |
