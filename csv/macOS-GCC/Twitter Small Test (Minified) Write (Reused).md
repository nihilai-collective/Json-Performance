
----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13278.2 | 2.75988 | 23.9401ms | 2963 | 4890 | 168683 | 212.81 | 0.0892883 | 1(Win) | true |
| simdjson (reflection) | 10407.9 | 3.25309 | 30.3519ms | 2963 | 2560 | 199697 | 271.5 | 1.84382 | 2(Loss) | true |
| Glaze | 3334.99 | 0.985895 | 81.7638ms | 2963 | 2560 | 178639 | 847.3 | 0.201041 | 3(Loss) | true |
