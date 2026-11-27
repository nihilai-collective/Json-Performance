
----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10378.4 | 0.290535 | 30.8029ms | 2963 | 4890 | 3059.89 | 272.27 | 0.448342 | 0.214869 | 1(Win) | true |
| Glaze | 4762.48 | 0.780684 | 64.3976ms | 2963 | 30 | 643.678 | 593.333 | 0.564972 | 0.502801 | 2(Loss) | true |
