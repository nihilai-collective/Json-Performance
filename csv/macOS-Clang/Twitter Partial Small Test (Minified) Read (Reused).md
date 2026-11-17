
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3883.93 | 0.147218 | 79.7122ms | 2889 | 40 | 43.625 | 709.375 | 0.335926 | 1(Win) | true |
| Jsonifier | 3854.12 | 0.2226 | 79.8002ms | 2889 | 160 | 405.151 | 714.862 | 0.0244742 | 2(Loss) | true |
| simdjson (ondemand) | 3633.34 | 0.402776 | 84.8604ms | 2889 | 40 | 373.138 | 758.3 | 0.19742 | 3(Loss) | true |
| Glaze | 2082.75 | 0.271599 | 146.805ms | 2889 | 80 | 1032.69 | 1322.85 | 3.32949 | 4(Loss) | true |
