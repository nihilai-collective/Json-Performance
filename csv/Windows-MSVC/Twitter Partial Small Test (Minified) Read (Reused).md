
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 5195.36 | 0.183265 | 56.9148ms | 2889 | 2560 | 2418.03 | 530.312 | 0.0589623 | 0.564434 | 1(Win) | true |
| Jsonifier | 5132.6 | 0.17819 | 57.9661ms | 2889 | 2560 | 2342.22 | 536.797 | 0.145328 | 0.571877 | 2(Loss) | true |
| simdjson (ondemand) | 4135.03 | 0.151765 | 70.6534ms | 2889 | 4890 | 5000.21 | 666.299 | 0.916391 | 0.714824 | 3(Loss) | true |
| Glaze | 2937.74 | 0.155217 | 100.927ms | 2889 | 2560 | 5424.85 | 937.852 | 0.523363 | 0.99858 | 4(Loss) | true |
