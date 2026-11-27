
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3569.59 | 0.0742113 | 79.6033ms | 2632 | 160 | 43.5707 | 703.181 | 0.0506883 | 0.668401 | 1(Win) | true |
| Jsonifier (two-stage) | 2802.27 | 0.0589871 | 99.7579ms | 2632 | 640 | 178.668 | 895.728 | 0.264099 | 0.857813 | 2(Loss) | true |
| Glaze | 2476.58 | 0.094332 | 109.945ms | 2632 | 40 | 36.5635 | 1013.52 | 0.0599855 | 0.974943 | 3(Loss) | true |
| simdjson (ondemand) | 1739.39 | 0.0593441 | 155.541ms | 2632 | 320 | 234.684 | 1443.08 | 0.00736329 | 1.39476 | 4(Loss) | true |
