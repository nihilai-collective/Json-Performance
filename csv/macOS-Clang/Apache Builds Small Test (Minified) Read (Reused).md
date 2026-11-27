
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2092.43 | 0.0877476 | 149.207ms | 2632 | 320 | 354.561 | 1199.6 | 0.0122422 | 1(Win) | true |
| Jsonifier (two-stage) | 1765.33 | 0.147649 | 169.108ms | 2632 | 2560 | 11282.9 | 1421.87 | 0.0548601 | 2(Loss) | true |
| Glaze | 1422.62 | 0.233939 | 204.498ms | 2632 | 4890 | 83312.3 | 1764.4 | 2.43151 | 3(Loss) | true |
| simdjson (ondemand) | 1078.3 | 0.675199 | 274.634ms | 2632 | 30 | 7410.99 | 2327.8 | 0.0601788 | 4(Loss) | true |
