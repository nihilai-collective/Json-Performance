
----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13212.1 | 0.19373 | 24.1496ms | 2963 | 160 | 27.4686 | 213.875 | 0.0233836 | 0.164595 | 1(Win) | true |
| Glaze | 5311.3 | 0.0532268 | 56.3038ms | 2963 | 640 | 51.3218 | 532.023 | 0.148094 | 0.443995 | 2(Loss) | true |
