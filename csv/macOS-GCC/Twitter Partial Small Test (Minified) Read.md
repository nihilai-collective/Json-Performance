
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 3568.87 | 2.19131 | 82.432ms | 2889 | 640 | 183157 | 772 | 2.55048 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 3462.37 | 0.786273 | 83.234ms | 2889 | 4890 | 191428 | 795.746 | 0.556558 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3351.25 | 0.743539 | 85.7661ms | 2889 | 4890 | 182725 | 822.132 | 1.47031 | 3(Tie) | true |
| Jsonifier STATISTICAL TIE | 3262.09 | 1.62342 | 84.011ms | 2889 | 1280 | 240644 | 844.6 | 3 | 3(Tie) | true |
| Glaze | 2381.14 | 0.774394 | 119.221ms | 2889 | 4890 | 392607 | 1157.08 | 0.122735 | 5(Loss) | true |
