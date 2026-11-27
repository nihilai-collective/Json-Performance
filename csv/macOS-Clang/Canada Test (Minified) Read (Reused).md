
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 612.823 | 0.157427 | 5681.13ms | 2090234 | 40 | 1.04892e+09 | 3.25282e+06 | 0.0245811 | 1(Win) | true |
| simdjson (ondemand) | 564.278 | 0.147409 | 6092.28ms | 2090234 | 80 | 2.1694e+09 | 3.53266e+06 | 0.347166 | 2(Loss) | true |
