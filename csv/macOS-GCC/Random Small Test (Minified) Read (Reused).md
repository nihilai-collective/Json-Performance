
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1114.32 | 0.210348 | 516.448ms | 4926 | 4890 | 384550 | 4215.83 | 1.57971 | 1(Win) | true |
| simdjson (ondemand) | 691.667 | 0.184655 | 775.862ms | 4926 | 2560 | 402679 | 6792 | 0.632022 | 2(Loss) | true |
