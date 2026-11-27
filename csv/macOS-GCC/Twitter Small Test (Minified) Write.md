
----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11865.5 | 2.58596 | 26.1901ms | 2963 | 4890 | 185458 | 238.148 | 1.99668 | 1(Win) | true |
| simdjson (reflection) | 9258.64 | 3.05208 | 32.5061ms | 2963 | 2560 | 222127 | 305.2 | 1.19363 | 2(Loss) | true |
| Glaze | 3048.97 | 0.630396 | 94.4571ms | 2963 | 4890 | 166914 | 926.783 | 0.506407 | 3(Loss) | true |
