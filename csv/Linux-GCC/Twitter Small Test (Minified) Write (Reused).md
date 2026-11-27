
----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12471.5 | 0.377917 | 25.2563ms | 2963 | 40 | 29.3276 | 226.575 | 0.387683 | 0.176738 | 1(Win) | true |
| simdjson (reflection) | 11069.4 | 0.105456 | 28.1514ms | 2963 | 640 | 46.3812 | 255.275 | 0.00856846 | 0.200329 | 2(Loss) | true |
| Glaze | 5645.83 | 0.0669916 | 53.3335ms | 2963 | 160 | 17.9874 | 500.5 | 0.0524201 | 0.415824 | 3(Loss) | true |
