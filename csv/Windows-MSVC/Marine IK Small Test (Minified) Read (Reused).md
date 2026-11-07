
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 638.186 | 0.17417 | 858.301ms | 4604 | 40 | 5743.59 | 6880 | 0.0969932 | 3.86849 | 1(Win) | true |
| Jsonifier (two-stage) | 608.624 | 0.172521 | 896.897ms | 4604 | 4890 | 757469 | 7214.17 | 0.427849 | 4.05123 | 2(Loss) | true |
| simdjson (ondemand) | 195.259 | 0.129229 | 2373.63ms | 4604 | 30 | 25333.3 | 22486.7 | 0.029656 | 12.6649 | 3(Loss) | true |
| Glaze | 179.584 | 0.258787 | 2677.88ms | 4604 | 320 | 1.28107e+06 | 24449.4 | 0.161307 | 13.7727 | 4(Loss) | true |
