
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7408.01 | 0.262687 | 52.4098ms | 3808 | 40 | 66.3327 | 490.225 | 0.98465 | 0.313386 | 1(Win) | true |
| Jsonifier (two-stage) | 7089.49 | 0.231169 | 53.698ms | 3808 | 40 | 56.0897 | 512.25 | 0.230475 | 0.329766 | 2(Loss) | true |
| Jsonifier | 6855.51 | 0.666339 | 53.3092ms | 3808 | 30 | 373.789 | 529.733 | 0.0691693 | 0.342717 | 3(Loss) | true |
| Glaze | 3662.93 | 0.0721834 | 103.118ms | 3808 | 160 | 81.9465 | 991.444 | 0.157979 | 0.656432 | 4(Loss) | true |
