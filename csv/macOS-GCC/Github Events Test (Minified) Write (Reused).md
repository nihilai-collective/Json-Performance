
----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13191.5 | 0.443551 | 405.26ms | 58581 | 2560 | 903346 | 4235.1 | 0.719677 | 1(Win) | true |
| simdjson (reflection) | 11715.1 | 0.46073 | 532.101ms | 58581 | 1280 | 617903 | 4768.8 | 0.100756 | 2(Loss) | true |
| Glaze | 4027.97 | 0.375284 | 1331.41ms | 58581 | 1280 | 3.46793e+06 | 13869.8 | 0.166103 | 3(Loss) | true |
