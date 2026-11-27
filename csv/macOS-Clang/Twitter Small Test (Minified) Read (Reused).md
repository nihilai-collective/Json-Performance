
----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1989.33 | 0.059283 | 149.843ms | 2821 | 2560 | 1645.48 | 1352.37 | 0.400462 | 1(Win) | true |
| simdjson (ondemand) | 1624.52 | 0.126097 | 180.462ms | 2821 | 2560 | 11163.7 | 1656.07 | 0.239987 | 2(Loss) | true |
