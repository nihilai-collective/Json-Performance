
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4109.19 | 0.0547706 | 73.1112ms | 2889 | 1280 | 172.619 | 670.489 | 0.00279639 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4108.32 | 0.0773002 | 72.9961ms | 2889 | 640 | 171.992 | 670.631 | 0.244506 | 1(Tie) | true |
| simdjson (ondemand) | 3746.61 | 0.337105 | 79.5261ms | 2889 | 80 | 491.63 | 735.375 | 0.433267 | 3(Loss) | true |
| Glaze | 2295.29 | 0.0840696 | 126.359ms | 2889 | 640 | 651.744 | 1200.35 | 0.0835086 | 4(Loss) | true |
