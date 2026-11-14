
----
### Random Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1200.38 | 0.101289 | 681.216ms | 8150 | 2560 | 110113 | 6474.96 | 0.0253082 | 1(Win) | true |
| simdjson (ondemand) | 587.616 | 0.0887288 | 1365.93ms | 8150 | 40 | 5509.56 | 13227.1 | 0.0267831 | 2(Loss) | true |
