
----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14138 | 0.107605 | 16.2873ms | 1996 | 1280 | 26.8671 | 134.64 | 0.242552 | 0.14103 | 1(Win) | true |
| simdjson (reflection) | 10982.4 | 0.0790766 | 19.9335ms | 1996 | 2560 | 48.0906 | 173.325 | 0.13976 | 0.192145 | 2(Loss) | true |
| Glaze | 5598.53 | 0.280132 | 36.8625ms | 1996 | 640 | 580.601 | 340.006 | 0.0854034 | 0.406752 | 3(Loss) | true |
