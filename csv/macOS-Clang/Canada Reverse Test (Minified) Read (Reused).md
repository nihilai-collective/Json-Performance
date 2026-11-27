
----
### Canada Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 570.598 | 0.568658 | 6146.21ms | 2090234 | 30 | 1.184e+10 | 3.49353e+06 | 0.196404 | 1(Win) | true |
| simdjson (ondemand) | 514.491 | 0.186123 | 6762.13ms | 2090234 | 30 | 1.56012e+09 | 3.87451e+06 | 0.722607 | 2(Loss) | true |
