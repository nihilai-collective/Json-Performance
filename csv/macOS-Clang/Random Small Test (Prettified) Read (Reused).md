
----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2288.04 | 0.0538556 | 427.284ms | 8051 | 160 | 522.581 | 3355.72 | 0.0787214 | 1(Win) | true |
| Jsonifier (two-stage) | 2015.28 | 0.0698511 | 456.106ms | 8051 | 80 | 566.587 | 3809.91 | 0.0154227 | 2(Loss) | true |
| Glaze | 1506.5 | 0.104369 | 596.759ms | 8051 | 160 | 4527.2 | 5096.61 | 0.17727 | 3(Loss) | true |
| simdjson (ondemand) | 1179.95 | 0.0689633 | 754.536ms | 8051 | 4890 | 98473.4 | 6507.09 | 0.039121 | 4(Loss) | true |
